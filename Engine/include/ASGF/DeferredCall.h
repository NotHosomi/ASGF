#pragma once
#include <vector>
#include <functional>
#include "Timer.h"

using DeferredCallHandle = int;

namespace ASGF
{

	DeferredCallHandle DeferCall(std::function<void()> hFunc, int delayMils);
	DeferredCallHandle DeferCall(std::function<void(DeferredCallHandle hHandle)> hFunc, int delayMils);
	void ClearPendingDeferredCalls();
	void RemovePendingDeferredCall(DeferredCallHandle nHandle);

	namespace _Internal
	{
		void ProcessDeferredCalls();
	}
}