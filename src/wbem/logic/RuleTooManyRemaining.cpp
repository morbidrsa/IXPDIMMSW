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
 * Rule that checks a MemoryAllocationRequest to make sure only one extent is
 * set to remaining
 */

#include "RuleTooManyRemaining.h"
#include <exception/NvmExceptionBadRequest.h>
#include <LogEnterExit.h>

wbem::logic::RuleTooManyRemaining::RuleTooManyRemaining()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
}

wbem::logic::RuleTooManyRemaining::~RuleTooManyRemaining()
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);
}

void wbem::logic::RuleTooManyRemaining::verify(const MemoryAllocationRequest &request)
{
	LogEnterExit logging(__FUNCTION__, __FILE__, __LINE__);

	int remainingCount = 0;
	if (request.memoryCapacity == REQUEST_REMAINING_CAPACITY)
	{
		remainingCount++;
	}
	if (request.storageRemaining)
	{
		remainingCount++;
	}
	for (std::vector<AppDirectExtent>::const_iterator adIter = request.appDirectExtents.begin();
			adIter != request.appDirectExtents.end(); adIter++)
	{
		if (adIter->capacity == REQUEST_REMAINING_CAPACITY)
		{
			remainingCount++;
		}
	}
	if (remainingCount > 1)
	{
		throw exception::NvmExceptionBadRequestRemaining();
	}
}
