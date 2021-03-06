/*
 * Copyright (c) 2016, Intel Corporation
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

#include <core/exceptions/InvalidArgumentException.h>
#include <core/exceptions/LibraryException.h>
#include "NvmLibrary.h"
#include "NvmLibrary.h"
#include "Helper.h"

namespace core
{

NvmLibrary &NvmLibrary::getNvmLibrary()
{
	LogEnterExit(__FUNCTION__, __FILE__, __LINE__);
	static NvmLibrary *result = new NvmLibrary();
	return *result;
}

NvmLibrary::NvmLibrary(const LibWrapper &lib) : m_lib(lib)
{
	LogEnterExit(__FUNCTION__, __FILE__, __LINE__);
}

NvmLibrary::NvmLibrary(const NvmLibrary &other) : m_lib(other.m_lib)
{
	LogEnterExit(__FUNCTION__, __FILE__, __LINE__);
}

NvmLibrary &NvmLibrary::operator=(const NvmLibrary &other)
{
	return *this;
}

NvmLibrary::~NvmLibrary()
{
	LogEnterExit(__FUNCTION__, __FILE__, __LINE__);
}

struct host NvmLibrary::getHost()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	struct host result;
	rc = m_lib.getHost(&result);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

	return result;

}

std::string NvmLibrary::getHostName()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	char result[NVM_COMPUTERNAME_LEN];
	rc = m_lib.getHostName(result, NVM_COMPUTERNAME_LEN);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

	return std::string(result);

}

struct sw_inventory NvmLibrary::getSwInventory()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	struct sw_inventory result;
	rc = m_lib.getSwInventory(&result);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

	return result;

}

int NvmLibrary::getSocketCount()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	rc = m_lib.getSocketCount();
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}
	return rc;

}

std::vector<struct socket> NvmLibrary::getSockets()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	std::vector<struct socket> result;
	rc = m_lib.getSocketCount();
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}
	int count = rc;
	struct socket fromLib[count];

	rc = m_lib.getSockets(fromLib, count);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

	for (int i = 0; i < count; i++)
	{
		result.push_back(fromLib[i]);
	}
	return result;

}

struct socket NvmLibrary::getSocket(const NVM_UINT16 socketId)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	struct socket result;
	rc = m_lib.getSocket(socketId, &result);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

	return result;

}

struct nvm_capabilities NvmLibrary::getNvmCapabilities()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	struct nvm_capabilities result;
	rc = m_lib.getNvmCapabilities(&result);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

	return result;

}

struct device_capacities NvmLibrary::getNvmCapacities()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	struct device_capacities result;
	rc = m_lib.getNvmCapacities(&result);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

	return result;

}

int NvmLibrary::getMemoryTopologyCount()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	rc = m_lib.getMemoryTopologyCount();
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}
	return rc;

}

std::vector<struct memory_topology> NvmLibrary::getMemoryTopology()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	std::vector<struct memory_topology> result;
	rc = m_lib.getMemoryTopologyCount();
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}
	int count = rc;
	struct memory_topology fromLib[count];

	rc = m_lib.getMemoryTopology(fromLib, count);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

	for (int i = 0; i < count; i++)
	{
		result.push_back(fromLib[i]);
	}
	return result;

}

int NvmLibrary::getDeviceCount()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	rc = m_lib.getDeviceCount();
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}
	return rc;

}

struct device_discovery NvmLibrary::getDeviceDiscovery(const std::string &guid)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	NVM_GUID lib_guid;
	core::Helper::stringToGuid(guid, lib_guid);

	struct device_discovery result;
	rc = m_lib.getDeviceDiscovery(lib_guid, &result);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

	return result;

}

std::vector<struct device_discovery> NvmLibrary::getDevices()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	std::vector<struct device_discovery> result;
	rc = m_lib.getDeviceCount();
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}
	int count = rc;
	struct device_discovery fromLib[count];
	memset(fromLib, 0, sizeof (struct device_discovery) * count);

	rc = m_lib.getDevices(fromLib, count);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

	for (int i = 0; i < count; i++)
	{
		result.push_back(fromLib[i]);
	}
	return result;

}

struct device_status NvmLibrary::getDeviceStatus(const std::string &deviceGuid)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	NVM_GUID lib_deviceGuid;
	core::Helper::stringToGuid(deviceGuid, lib_deviceGuid);

	struct device_status result;
	rc = m_lib.getDeviceStatus(lib_deviceGuid, &result);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

	return result;

}

struct device_settings NvmLibrary::getDeviceSettings(const std::string &deviceGuid)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	NVM_GUID lib_deviceGuid;
	core::Helper::stringToGuid(deviceGuid, lib_deviceGuid);

	struct device_settings result;
	rc = m_lib.getDeviceSettings(lib_deviceGuid, &result);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

	return result;

}

void NvmLibrary::modifyDeviceSettings(const std::string &deviceGuid,
	const struct device_settings &pSettings)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	NVM_GUID lib_deviceGuid;
	core::Helper::stringToGuid(deviceGuid, lib_deviceGuid);

	rc = m_lib.modifyDeviceSettings(lib_deviceGuid, &pSettings);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

}

struct device_details NvmLibrary::getDeviceDetails(const std::string &deviceGuid)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	NVM_GUID lib_deviceGuid;
	core::Helper::stringToGuid(deviceGuid, lib_deviceGuid);

	struct device_details result;
	rc = m_lib.getDeviceDetails(lib_deviceGuid, &result);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

	return result;

}

struct device_performance NvmLibrary::getDevicePerformance(const std::string &deviceGuid)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	NVM_GUID lib_deviceGuid;
	core::Helper::stringToGuid(deviceGuid, lib_deviceGuid);

	struct device_performance result;
	rc = m_lib.getDevicePerformance(lib_deviceGuid, &result);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

	return result;

}

void NvmLibrary::updateDeviceFw(const std::string &deviceGuid, const std::string path,
	const bool activate, const bool force)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	NVM_GUID lib_deviceGuid;
	core::Helper::stringToGuid(deviceGuid, lib_deviceGuid);

	char lib_path[path.size()];
	s_strcpy(lib_path, path.c_str(), path.size());

	rc = m_lib.updateDeviceFw(lib_deviceGuid, lib_path, path.size(), activate, force);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

}

void NvmLibrary::examineDeviceFw(const std::string &deviceGuid, const std::string path,
	std::string imageVersion)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	NVM_GUID lib_deviceGuid;
	core::Helper::stringToGuid(deviceGuid, lib_deviceGuid);

	char lib_path[path.size()];
	s_strcpy(lib_path, path.c_str(), path.size());

	char lib_imageVersion[imageVersion.size()];
	s_strcpy(lib_imageVersion, imageVersion.c_str(), imageVersion.size());

	rc = m_lib.examineDeviceFw(lib_deviceGuid, lib_path, path.size(), lib_imageVersion,
		imageVersion.size());
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

}

void NvmLibrary::setPassphrase(const std::string &deviceGuid, const std::string oldPassphrase,
	const std::string newPassphrase)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	NVM_GUID lib_deviceGuid;
	core::Helper::stringToGuid(deviceGuid, lib_deviceGuid);

	char lib_oldPassphrase[oldPassphrase.size()];
	s_strcpy(lib_oldPassphrase, oldPassphrase.c_str(), oldPassphrase.size());

	char lib_newPassphrase[newPassphrase.size()];
	s_strcpy(lib_newPassphrase, newPassphrase.c_str(), newPassphrase.size());

	rc = m_lib.setPassphrase(lib_deviceGuid, lib_oldPassphrase, oldPassphrase.size(),
		lib_newPassphrase, newPassphrase.size());
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

}

void NvmLibrary::removePassphrase(const std::string &deviceGuid, const std::string passphrase)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	NVM_GUID lib_deviceGuid;
	core::Helper::stringToGuid(deviceGuid, lib_deviceGuid);

	char lib_passphrase[passphrase.size()];
	s_strcpy(lib_passphrase, passphrase.c_str(), passphrase.size());

	rc = m_lib.removePassphrase(lib_deviceGuid, lib_passphrase, passphrase.size());
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

}

void NvmLibrary::unlockDevice(const std::string &deviceGuid, const std::string passphrase)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	NVM_GUID lib_deviceGuid;
	core::Helper::stringToGuid(deviceGuid, lib_deviceGuid);

	char lib_passphrase[passphrase.size()];
	s_strcpy(lib_passphrase, passphrase.c_str(), passphrase.size());

	rc = m_lib.unlockDevice(lib_deviceGuid, lib_passphrase, passphrase.size());
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

}

void NvmLibrary::eraseDevice(const std::string &deviceGuid, const erase_type type,
	const std::string passphrase)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	NVM_GUID lib_deviceGuid;
	core::Helper::stringToGuid(deviceGuid, lib_deviceGuid);

	char lib_passphrase[passphrase.size()];
	s_strcpy(lib_passphrase, passphrase.c_str(), passphrase.size());

	rc = m_lib.eraseDevice(lib_deviceGuid, type, lib_passphrase, passphrase.size());
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

}

int NvmLibrary::getJobCount()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	rc = m_lib.getJobCount();
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}
	return rc;

}

std::vector<struct job> NvmLibrary::getJobs()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	std::vector<struct job> result;
	rc = m_lib.getJobCount();
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}
	int count = rc;
	struct job fromLib[count];

	rc = m_lib.getJobs(fromLib, count);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

	for (int i = 0; i < count; i++)
	{
		result.push_back(fromLib[i]);
	}
	return result;

}

int NvmLibrary::getPoolCount()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	rc = m_lib.getPoolCount();
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}
	return rc;

}

std::vector<struct pool> NvmLibrary::getPools()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	std::vector<struct pool> result;
	rc = m_lib.getPoolCount();
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}
	int count = rc;
	struct pool fromLib[count];

	rc = m_lib.getPools(fromLib, count);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

	for (int i = 0; i < count; i++)
	{
		result.push_back(fromLib[i]);
	}
	return result;

}

struct pool NvmLibrary::getPool(const std::string &poolGuid)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	NVM_GUID lib_poolGuid;
	core::Helper::stringToGuid(poolGuid, lib_poolGuid);

	struct pool result;
	rc = m_lib.getPool(lib_poolGuid, &result);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

	return result;

}

struct possible_namespace_ranges NvmLibrary::getAvailablePersistentSizeRange(
	const std::string &poolGuid)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	NVM_GUID lib_poolGuid;
	core::Helper::stringToGuid(poolGuid, lib_poolGuid);

	struct possible_namespace_ranges result;
	rc = m_lib.getAvailablePersistentSizeRange(lib_poolGuid, &result);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

	return result;

}

void NvmLibrary::createConfigGoal(const std::string &deviceGuid, struct config_goal &pGoal)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	NVM_GUID lib_deviceGuid;
	core::Helper::stringToGuid(deviceGuid, lib_deviceGuid);

	rc = m_lib.createConfigGoal(lib_deviceGuid, &pGoal);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

}

struct config_goal NvmLibrary::getConfigGoal(const std::string &deviceGuid)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	NVM_GUID lib_deviceGuid;
	core::Helper::stringToGuid(deviceGuid, lib_deviceGuid);

	struct config_goal result;
	rc = m_lib.getConfigGoal(lib_deviceGuid, &result);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

	return result;

}

void NvmLibrary::deleteConfigGoal(const std::string &deviceGuid)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	NVM_GUID lib_deviceGuid;
	core::Helper::stringToGuid(deviceGuid, lib_deviceGuid);

	rc = m_lib.deleteConfigGoal(lib_deviceGuid);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

}

void NvmLibrary::dumpConfig(const std::string &deviceGuid, const std::string file,
	const bool append)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	NVM_GUID lib_deviceGuid;
	core::Helper::stringToGuid(deviceGuid, lib_deviceGuid);

	char lib_file[file.size()];
	s_strcpy(lib_file, file.c_str(), file.size());

	rc = m_lib.dumpConfig(lib_deviceGuid, lib_file, file.size(), append);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

}

void NvmLibrary::loadConfig(const std::string &deviceGuid, const std::string file)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	NVM_GUID lib_deviceGuid;
	core::Helper::stringToGuid(deviceGuid, lib_deviceGuid);

	char lib_file[file.size()];
	s_strcpy(lib_file, file.c_str(), file.size());

	rc = m_lib.loadConfig(lib_deviceGuid, lib_file, file.size());
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

}

int NvmLibrary::getNamespaceCount()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	rc = m_lib.getNamespaceCount();
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}
	return rc;

}

int NvmLibrary::getDeviceNamespaceCount(const std::string &deviceGuid,
	const enum namespace_type type)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	NVM_GUID lib_deviceGuid;
	core::Helper::stringToGuid(deviceGuid, lib_deviceGuid);

	rc = m_lib.getDeviceNamespaceCount(lib_deviceGuid, type);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}
	return rc;

}

std::vector<struct namespace_discovery> NvmLibrary::getNamespaces()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	std::vector<struct namespace_discovery> result;
	rc = m_lib.getNamespaceCount();
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}
	int count = rc;
	struct namespace_discovery fromLib[count];

	rc = m_lib.getNamespaces(fromLib, count);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

	for (int i = 0; i < count; i++)
	{
		result.push_back(fromLib[i]);
	}
	return result;

}

struct namespace_details NvmLibrary::getNamespaceDetails(const std::string &namespaceGuid)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	NVM_GUID lib_namespaceGuid;
	core::Helper::stringToGuid(namespaceGuid, lib_namespaceGuid);

	struct namespace_details result;
	rc = m_lib.getNamespaceDetails(lib_namespaceGuid, &result);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

	return result;

}

std::string NvmLibrary::createNamespace(const std::string &pool_guid,
	struct namespace_create_settings &p_settings, const struct interleave_format &p_format,
	const bool allow_adjustment)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;
	NVM_GUID lib_pool_guid;
	core::Helper::stringToGuid(pool_guid, lib_pool_guid);

	NVM_GUID fromLibNamespaceGuid;
	rc = m_lib.createNamespace(&fromLibNamespaceGuid, lib_pool_guid, &p_settings, &p_format,
		allow_adjustment);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}
	return core::Helper::guidToString(fromLibNamespaceGuid);
}

void NvmLibrary::modifyNamespaceName(const std::string &namespaceGuid,
	const std::string &name)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	NVM_GUID lib_namespaceGuid;
	core::Helper::stringToGuid(namespaceGuid, lib_namespaceGuid);
	NVM_NAMESPACE_NAME lib_name;
	memmove(lib_name, name.c_str(), NVM_NAMESPACE_NAME_LEN);
	rc = m_lib.modifyNamespaceName(lib_namespaceGuid, lib_name);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

}

int NvmLibrary::modifyNamespaceBlockCount(const std::string &namespaceGuid,
	const NVM_UINT64 blockCount, bool allowAdjustment)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	NVM_GUID lib_namespaceGuid;
	core::Helper::stringToGuid(namespaceGuid, lib_namespaceGuid);

	rc = m_lib.modifyNamespaceBlockCount(lib_namespaceGuid, blockCount, allowAdjustment);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}
	return rc;

}

void NvmLibrary::modifyNamespaceEnabled(const std::string &namespaceGuid,
	const enum namespace_enable_state enabled)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	NVM_GUID lib_namespaceGuid;
	core::Helper::stringToGuid(namespaceGuid, lib_namespaceGuid);

	rc = m_lib.modifyNamespaceEnabled(lib_namespaceGuid, enabled);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

}

void NvmLibrary::deleteNamespace(const std::string &namespaceGuid)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	NVM_GUID lib_namespaceGuid;
	core::Helper::stringToGuid(namespaceGuid, lib_namespaceGuid);

	rc = m_lib.deleteNamespace(lib_namespaceGuid);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

}

void NvmLibrary::adjustCreateNamespaceBlockCount(const std::string &poolGuid,
	struct namespace_create_settings &pSettings, const struct interleave_format &pFormat)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	NVM_GUID lib_poolGuid;
	core::Helper::stringToGuid(poolGuid, lib_poolGuid);

	rc = m_lib.adjustCreateNamespaceBlockCount(lib_poolGuid, &pSettings, &pFormat);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}
}

void NvmLibrary::adjustModifyNamespaceBlockCount(const std::string &namespaceGuid,
	NVM_UINT64 &pBlockCount)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	NVM_GUID lib_namespaceGuid;
	core::Helper::stringToGuid(namespaceGuid, lib_namespaceGuid);

	rc = m_lib.adjustModifyNamespaceBlockCount(lib_namespaceGuid, &pBlockCount);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}
}

std::vector<struct sensor> NvmLibrary::getSensors(const std::string &deviceGuid)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	NVM_GUID lib_deviceGuid;
	core::Helper::stringToGuid(deviceGuid, lib_deviceGuid);

	std::vector<struct sensor> result;
	struct sensor sensors[NVM_MAX_DEVICE_SENSORS];
	rc = m_lib.getSensors(lib_deviceGuid, sensors, NVM_MAX_DEVICE_SENSORS);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

	for (int i = 0; i < NVM_MAX_DEVICE_SENSORS; i++)
	{
		result.push_back(sensors[i]);
	}

	return result;

}

struct sensor NvmLibrary::getSensor(const std::string &deviceGuid, const enum sensor_type type)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	NVM_GUID lib_deviceGuid;
	core::Helper::stringToGuid(deviceGuid, lib_deviceGuid);

	struct sensor result;
	rc = m_lib.getSensor(lib_deviceGuid, type, &result);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

	return result;

}

void NvmLibrary::setSensorSettings(const std::string &deviceGuid, const enum sensor_type type,
	const struct sensor_settings &pSettings)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	NVM_GUID lib_deviceGuid;
	core::Helper::stringToGuid(deviceGuid, lib_deviceGuid);

	rc = m_lib.setSensorSettings(lib_deviceGuid, type, &pSettings);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

}

void NvmLibrary::addEventNotify(const enum event_type type,
	void (*pEventCallback)(struct event *pEvent))
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	rc = m_lib.addEventNotify(type, pEventCallback);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

}

void NvmLibrary::removeEventNotify(const int callbackId)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	rc = m_lib.removeEventNotify(callbackId);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

}

int NvmLibrary::getEventCount(const struct event_filter &pFilter)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	rc = m_lib.getEventCount(&pFilter);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}
	return rc;

}

std::vector<struct event> NvmLibrary::getEvents(const struct event_filter &pFilter)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	std::vector<struct event> result;
	rc = m_lib.getEventCount(&pFilter);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}
	int count = rc;
	struct event fromLib[count];

	rc = m_lib.getEvents(&pFilter, fromLib, count);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

	for (int i = 0; i < count; i++)
	{
		result.push_back(fromLib[i]);
	}
	return result;

}

void NvmLibrary::purgeEvents(const struct event_filter &pFilter)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	rc = m_lib.purgeEvents(&pFilter);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

}

void NvmLibrary::acknowledgeEvent(NVM_UINT32 eventId)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	rc = m_lib.acknowledgeEvent(eventId);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

}

void NvmLibrary::saveState(const std::string name)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	char lib_name[name.size()];
	s_strcpy(lib_name, name.c_str(), name.size());

	rc = m_lib.saveState(lib_name, name.size());
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

}

void NvmLibrary::purgeStateData()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	rc = m_lib.purgeStateData();
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

}

void NvmLibrary::gatherSupport(const std::string supportFile)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	char lib_supportFile[supportFile.size()];
	s_strcpy(lib_supportFile, supportFile.c_str(), supportFile.size());

	rc = m_lib.gatherSupport(lib_supportFile, supportFile.size());
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

}

void NvmLibrary::runDiagnostic(const std::string &deviceGuid, const struct diagnostic &pDiagnostic,
	NVM_UINT32 &pResults)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	NVM_GUID lib_deviceGuid;
	core::Helper::stringToGuid(deviceGuid, lib_deviceGuid);

	rc = m_lib.runDiagnostic(lib_deviceGuid, &pDiagnostic, &pResults);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

}

enum fw_log_level NvmLibrary::getFwLogLevel(const std::string &deviceGuid)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	NVM_GUID lib_deviceGuid;
	core::Helper::stringToGuid(deviceGuid, lib_deviceGuid);

	enum fw_log_level result;
	rc = m_lib.getFwLogLevel(lib_deviceGuid, &result);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

	return result;

}

void NvmLibrary::setFwLogLevel(const std::string &deviceGuid, const enum fw_log_level logLevel)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	NVM_GUID lib_deviceGuid;
	core::Helper::stringToGuid(deviceGuid, lib_deviceGuid);

	rc = m_lib.setFwLogLevel(lib_deviceGuid, logLevel);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

}

struct device_fw_info NvmLibrary::getDeviceFwInfo(const std::string &device_guid)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	NVM_GUID lib_device_guid;
	core::Helper::stringToGuid(device_guid, lib_device_guid);

	struct device_fw_info result;
	rc = m_lib.getDeviceFwInfo(lib_device_guid, &result);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

	return result;

}

void NvmLibrary::injectDeviceError(const std::string &deviceGuid, const struct device_error &pError)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	NVM_GUID lib_deviceGuid;
	core::Helper::stringToGuid(deviceGuid, lib_deviceGuid);

	rc = m_lib.injectDeviceError(lib_deviceGuid, &pError);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

}

void NvmLibrary::clearInjectedDeviceError(const std::string &deviceGuid,
	const struct device_error &pError)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	NVM_GUID lib_deviceGuid;
	core::Helper::stringToGuid(deviceGuid, lib_deviceGuid);

	rc = m_lib.clearInjectedDeviceError(lib_deviceGuid, &pError);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

}

void NvmLibrary::addSimulator(const std::string simulator)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	char lib_simulator[simulator.size()];
	s_strcpy(lib_simulator, simulator.c_str(), simulator.size());

	rc = m_lib.addSimulator(lib_simulator, simulator.size());
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

}

void NvmLibrary::removeSimulator()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	rc = m_lib.removeSimulator();
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

}

bool NvmLibrary::isDebugLoggingEnabled()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	rc = m_lib.debugLoggingEnabled();
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

	return rc == 1;

}

void NvmLibrary::toggleDebugLogging(const bool enabled)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	rc = m_lib.toggleDebugLogging(enabled);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

}

int NvmLibrary::getDebugLogCount()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	rc = m_lib.getDebugLogCount();
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}
	return rc;

}

std::vector<struct log> NvmLibrary::getDebugLogs()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	std::vector<struct log> result;
	rc = m_lib.getDebugLogCount();
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}
	int count = rc;
	struct log fromLib[count];

	rc = m_lib.getDebugLogs(fromLib, count);
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

	for (int i = 0; i < count; i++)
	{
		result.push_back(fromLib[i]);
	}
	return result;

}

void NvmLibrary::purgeDebugLog()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
	int rc;

	rc = m_lib.purgeDebugLog();
	if (rc < 0)
	{
		throw core::LibraryException(rc);
	}

}
}

