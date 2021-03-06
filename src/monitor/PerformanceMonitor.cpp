/*
 * Copyright (c) 2015 2016, Intel Corporation
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of Intel Corporation nor the names of its contributors
 *     may be used to endorse or promote products derived from this software
 *     without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * This file contains the implementation of the performance monitoring class
 * of the NvmMonitor service which periodically polls and stores performance metrics
 * for each manageable NVM-DIMM in the system.
 */

#include <string.h>
#include "PerformanceMonitor.h"
#include <LogEnterExit.h>
#include <guid/guid.h>
#include <string/s_str.h>
#include <persistence/config_settings.h>
#include <nvm_context.h>

monitor::PerformanceMonitor::PerformanceMonitor()
	: NvmMonitorBase(PERFORMANCE_MONITOR_NAME)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);

	// open a connection to the db
	m_pStore = get_lib_store();
	if (!m_pStore)
	{
		m_pStore = open_default_lib_store();
	}
}

monitor::PerformanceMonitor::~PerformanceMonitor()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);

	// close the db connection
	if (m_pStore)
	{
		close_lib_store();
	}
}

/*
 * Thread callback on monitor interval timer
 */
void monitor::PerformanceMonitor::monitor()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);

	// clear any existing context
	nvm_create_context();

	bool performanceDataAdded = false;

	// get list of manageable dimms
	std::vector<std::string> dimmList = getDimmList();
	for (std::vector<std::string>::const_iterator dimmGuidIter = dimmList.begin();
			dimmGuidIter != dimmList.end(); dimmGuidIter++)
	{
		std::string dimmGuidStr = *dimmGuidIter;
		NVM_GUID dimmGuid;
		str_to_guid(dimmGuidStr.c_str(), dimmGuid);

		// get performance data for the dimm
		struct device_performance devPerformance;
		memset(&devPerformance, 0, sizeof (devPerformance));
		int rc = nvm_get_device_performance(dimmGuid, &devPerformance);
		if (rc != NVM_SUCCESS)
		{
			COMMON_LOG_ERROR_F(
				"Failed to retrieve the performance data for "NVM_DIMM_NAME" %s", dimmGuidStr.c_str());
		}
		// store it in the db
		else if (storeDimmPerformanceData(dimmGuidStr, devPerformance))
		{
			performanceDataAdded = true;
		}
	}

	// trim the performance data if any new data is added
	if (performanceDataAdded)
	{
		trimPerformanceData();
	}

	// clean up
	dimmList.clear();
	nvm_free_context();
}

std::vector<std::string> monitor::PerformanceMonitor::getDimmList()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);

	std::vector<std::string> dimmList;
	int dimmCount = nvm_get_device_count();
	 // error getting dimm count
	if (dimmCount < 0)
	{
		COMMON_LOG_ERROR_F("nvm_get_device_count failed with error %d", dimmCount);
	}
	// at least one dimm
	else if (dimmCount > 0)
	{
		struct device_discovery dimms[dimmCount];
		dimmCount = nvm_get_devices(dimms, dimmCount);
		// error getting dimms
		if (dimmCount < 0)
		{
			COMMON_LOG_ERROR_F("nvm_get_devices failed with error %d", dimmCount);
		}
		 // at least one dimm
		else if (dimmCount > 0)
		{
			for (int i = 0; i < dimmCount; i++)
			{
				// only looks at manageable NVM-DIMMs
				if (dimms[i].manageability == MANAGEMENT_VALIDCONFIG)
				{
					NVM_GUID_STR guidStr;
					guid_to_str(dimms[i].guid, guidStr);
					dimmList.push_back(std::string(guidStr));
				}
			}
		}
	}
	return dimmList;
}

bool monitor::PerformanceMonitor::storeDimmPerformanceData(const std::string &dimmGuidStr,
		struct device_performance &performance)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	bool dimmPerformanceStored = false;

	struct db_performance performanceRow;
	memset(&performanceRow, 0, sizeof (performanceRow));

	// db_peformance.id will be auto generated by sqlite
	s_strcpy(performanceRow.dimm_guid, dimmGuidStr.c_str(), NVM_GUIDSTR_LEN);
	performanceRow.time = performance.time;
	performanceRow.bytes_read = performance.bytes_read;
	performanceRow.bytes_written = performance.bytes_written;
	performanceRow.read_reqs = performance.host_reads;
	performanceRow.host_write_cmds = performance.host_writes;
	performanceRow.block_reads = performance.block_reads;
	performanceRow.block_writes = performance.block_writes;

	if (db_add_performance(m_pStore, &performanceRow) != DB_SUCCESS)
	{
		COMMON_LOG_ERROR_F(
				"Failed to store performance metrics for "NVM_DIMM_NAME" %s", dimmGuidStr.c_str());
	}
	else
	{
		dimmPerformanceStored = true;
	}
	return dimmPerformanceStored;
}

void monitor::PerformanceMonitor::trimPerformanceData()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);

	// max and trim percent are configurable
	int maxPerformanceRows = 10000;
	int defaultTrimPercent = 30;
	int trimPercent = defaultTrimPercent;
	get_config_value_int(SQL_KEY_PERFORMANCE_LOG_MAX, &maxPerformanceRows);
	get_config_value_int(SQL_KEY_PERFORMANCE_LOG_TRIM_PERCENT, &trimPercent);
	if (trimPercent < 0)
		trimPercent = defaultTrimPercent;

	int currentPerformanceRows = 0;
	table_row_count(m_pStore, PERFORMANCE_TABLE_NAME.c_str(), &currentPerformanceRows);
	if (currentPerformanceRows > maxPerformanceRows)
	{
		// trim overage and additional % so we're not trimming every time
		int trimCount = currentPerformanceRows - maxPerformanceRows;
		trimCount += (((float)trimPercent)/100 * maxPerformanceRows);
		// make sure it's not greater than all
		if (trimCount > currentPerformanceRows)
		{
			trimCount = currentPerformanceRows;
		}
		char sql[1024];
		s_snprintf(sql, 1024,
				"DELETE FROM performance "
				"where id IN "
				"(SELECT id FROM performance ORDER BY time DESC LIMIT %d)",
				trimCount);
		if (db_run_custom_sql(m_pStore, sql) != DB_SUCCESS)
		{
			COMMON_LOG_ERROR("Failed to trim the stored performance metrics log");
		}
	}
}
