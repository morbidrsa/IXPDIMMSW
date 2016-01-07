/*
 * Copyright (c) 2015, Intel Corporation
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
 * This file contains the base class for Intel CIM provider classes.
 */

#ifndef    _WBEM_FRAMEWORK_NVMINSTANCE_FACTORY_H_
#define    _WBEM_FRAMEWORK_NVMINSTANCE_FACTORY_H_

#include <lib_interface/NvmApi.h>
#include <NvmStrings.h>
#include <intel_cim_framework/Types.h>

#include <intel_cim_framework/InstanceFactory.h>
#include <intel_cim_framework/Exception.h>
#include <intel_cim_framework/Instance.h>
#include <intel_cim_framework/ObjectPath.h>
#include <intel_cim_framework/Attribute.h>

namespace wbem
{
namespace framework_interface
{

/*!
 * The base class for Nvm CIM instance factories.
 */

class NVM_API NvmInstanceFactory : public framework::InstanceFactory
{
public:
	NvmInstanceFactory();

	virtual ~NvmInstanceFactory() {}
	static framework::InstanceFactory *getInstanceFactory(std::string className);

protected:
	wbem::lib_interface::NvmApi *m_pApi;
};

}
}
#endif  // #ifndef _WBEM_FRAMEWORK_NVMINSTANCE_FACTORY_H_