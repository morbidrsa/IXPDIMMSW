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

#include <libintelnvm-cim/Instance.h>
#include <LogEnterExit.h>
#include <nvm_types.h>
#include <libintelnvm-cim/ExceptionBadAttribute.h>
#include "FrameworkExtensions.h"

namespace wbem
{
void checkAttributesAreModifiable(
	wbem::framework::Instance *pInstance, wbem::framework::attributes_t &attributesToModify,
	wbem::framework::attribute_names_t modifiableAttributes)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);

	framework::attributes_t::iterator iter = attributesToModify.begin();

	for (; iter != attributesToModify.end(); iter++)
	{
		std::string attributeName = iter->first;

		framework::Attribute instanceAttr;
		if (pInstance->getAttribute(attributeName, instanceAttr) == NVM_SUCCESS)
		{
			if ((instanceAttr !=  iter->second) &&
				!isNameInAttributeNameList(modifiableAttributes, iter->first))
			{
				COMMON_LOG_ERROR_F("Cannot modify attribute %s", attributeName.c_str());
				throw framework::ExceptionBadAttribute(iter->first.c_str());
			}
		}
	}
}
}

