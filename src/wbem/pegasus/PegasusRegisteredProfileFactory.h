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
 * This file contains the provider for the RegisteredProfile instances.
 */

#ifndef PEGASUSREGISTEREDPROFILEFACTORY_H_
#define PEGASUSREGISTEREDPROFILEFACTORY_H_

#include <framework_interface/NvmInstanceFactory.h>

namespace wbem
{
namespace pegasus
{
static const std::string PGREGISTEREDPROFILE_CLASSNAME = "PG_RegisteredProfile";

/*!
 * CIM provider for PegasusRegisteredProfile instances.
 * This provider is only exposed in the interop namespace
 * The list of supported profiles is effectively static.
 */
class PegasusRegisteredProfileFactory : public framework_interface::NvmInstanceFactory
{
	public:
		/*!
		 * Destructor
		 */
		~PegasusRegisteredProfileFactory(){}

		/*!
		 * Determines if the two instances should be associated by the Association Class.
		 * @param associationClass
		 * @param pAntInstance
		 * @param pDepInstance
		 * @return true if associated
		 */
		bool isAssociated(const std::string &associationClass,
				framework::Instance *pAntInstance, framework::Instance *pDepInstance){return false;}
	protected:

		/*!
		 * Create a default list of attributes names to retrieve.
		 * We have to provide an implementation for this pure virtual function although it is never called.
		 */
		virtual void populateAttributeList(framework::attribute_names_t &attributes) throw (framework::Exception){};
};

} /* namespace pegasus */
} /* namespace wbem */

#endif /* PEGASUSREGISTEREDPROFILEFACTORY_H_ */