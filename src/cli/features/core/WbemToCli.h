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

#ifndef _CLI_NVMCLI_WBEMTOCLI_H_
#define _CLI_NVMCLI_WBEMTOCLI_H_

#include <nvm_management.h>

#include <libintelnvm-cli/PropertyListResult.h>
#include <libintelnvm-cli/ObjectListResult.h>
#include <libintelnvm-cim/Instance.h>
#include <libintelnvm-cli/SyntaxErrorBadValueResult.h>
#include <framework_interface/NvmInstanceFactory.h>

namespace cli
{
namespace nvmcli
{
class WbemToCli
{
public:
	/*
	 * Constructor
	 */
	WbemToCli();

	/*
	 * Destructor
	 */
	virtual ~WbemToCli();

	/*
	* For commands that support an optional -namespace target,
	* retrieve the namespace GUID(s) of the specified target
	* or all namespace GUIDs if not specified.
	*/
	virtual cli::framework::ErrorResult *getNamespaces(
		const framework::ParsedCommand &parsedCommand, std::vector<std::string> &namespaces);
	/*
	 * For commands that support the -pool target, verify the pool GUID specified
	 * or retrieve it if not specified
	 */
	virtual cli::framework::ErrorResult *checkPoolGuid(
		const framework::ParsedCommand &parsedCommand, std::string &poolGuid);

};
}
}
#endif // _CLI_NVMCLI_WBEMTOCLI_H_
