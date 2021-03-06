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
 * A class that accepts a request and performs memory allocation.
 */

#ifndef _WBEM_LOGIC_MEMORYALLOCATOR_H_
#define _WBEM_LOGIC_MEMORYALLOCATOR_H_

#include <vector>
#include "MemoryAllocationTypes.h"
#include "RequestRule.h"
#include "PostLayoutCheck.h"
#include <lib_interface/NvmApi.h>

#include <libintelnvm-cim/Exception.h>

namespace wbem
{
namespace logic
{

class NVM_API MemoryAllocator
{
	public:
		MemoryAllocator(const struct nvm_capabilities &systemCapabilities,
				const std::vector<struct device_discovery> &manageableDevices,
				const std::vector<struct pool> &pools,
				const NVM_UINT16 socketCount,
				lib_interface::NvmApi *pApi = NULL);
		virtual ~MemoryAllocator();

		/*
		 * Guaranteed non-NULL. If the new MemoryAllocator couldn't be created,
		 * throws an exception.
		 * Caller is responsible for freeing the pointer.
		 */
		static MemoryAllocator *getNewMemoryAllocator();

		MemoryAllocationLayout layout(const struct MemoryAllocationRequest &request);
		void allocate(struct MemoryAllocationLayout &layout);

		static NVM_UINT64 getTotalCapacitiesOfRequestedDimmsinB(const MemoryAllocationRequest& request);

	protected:
		void validateLayout(
				const struct MemoryAllocationRequest &request,
				const MemoryAllocationLayout layout);
		void validateRequest(const struct MemoryAllocationRequest &request);
		void populateRequestRules();
		void populatePostLayoutChecks();
		void deleteRequestRules();
		void deleteLayoutRules();

		std::vector<RequestRule *> m_requestRules;
		std::vector<PostLayoutCheck *> m_postLayoutChecks;

		struct nvm_capabilities m_systemCapabilities;
		std::vector<struct device_discovery> m_manageableDevices;
		std::vector<struct pool> m_pools;
		NVM_UINT16 m_socketCount;

		lib_interface::NvmApi *m_pLibApi;
};

} /* namespace logic */
} /* namespace wbem */

#endif /* _WBEM_LOGIC_MEMORYALLOCATOR_H_ */
