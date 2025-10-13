#include "include/ASGF/DeferredCall.h"
#include <algorithm>

namespace ASGF
{
	namespace _Internal
	{
		std::vector<T_DeferredCall> m_vDeferredCalls;
	}
}

void ASGF::DeferCall(std::function<void()> hFunc, int delayMils)
{
	_Internal::T_DeferredCall info;
	info.hFunc = hFunc;
	info.timer.SetDuration(delayMils);
	info.timer.Start();
	_Internal::m_vDeferredCalls.push_back(info);
}

void ASGF::ClearPendingDeferredCalls()
{
	_Internal::m_vDeferredCalls.clear();
}

void ASGF::_Internal::ProcessDeferredCalls()
{
	std::erase_if(m_vDeferredCalls, [](T_DeferredCall& obj)
		{
			if (obj.timer.Elapsed())
			{
				obj.hFunc();
				return true;
			}
			return false;
		});
}
