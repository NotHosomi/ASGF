#pragma once
#include <vector>
#include <functional>
#include "Timer.h"

namespace ASGF
{
	void DeferCall(std::function<void()> hFunc, int delayMils);
	void ClearPendingDeferredCalls();

	namespace _Internal
	{
		void ProcessDeferredCalls();
		struct T_DeferredCall
		{
			std::function<void()> hFunc;
			Timer timer;
		};
	}
}