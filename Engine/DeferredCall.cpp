#include "include/ASGF/DeferredCall.h"
#include <algorithm>
#include <map>
#include <queue>

#define MAX_DEFERRED_CALLS 1028

namespace ASGF
{
	namespace _Internal
	{
		struct T_DeferredCall
		{
			std::function<void()> hFunc;
			Timer timer;
		};
		std::map<DeferredCallHandle, T_DeferredCall> g_mDeferredCalls;
		std::queue<DeferredCallHandle> g_qFreedHandles;
		bool g_bOverflow = false;
	}
}

DeferredCallHandle ASGF::DeferCall(std::function<void()> hFunc, int delayMils)
{
	_Internal::T_DeferredCall info;
	info.hFunc = hFunc;
	info.timer.SetDuration(delayMils);
	info.timer.Start();

	DeferredCallHandle handle;
	if (!_Internal::g_bOverflow)
	{
		static DeferredCallHandle nextHandle = 0;
		handle = nextHandle;
		++nextHandle;
		if (nextHandle == MAX_DEFERRED_CALLS)
		{
			_Internal::g_bOverflow = true;
		}
	}
	else
	{
		handle = _Internal::g_qFreedHandles.front();
		_Internal::g_qFreedHandles.pop();
	}

	_Internal::g_mDeferredCalls.insert({ handle, info });
	return handle;
}

void ASGF::ClearPendingDeferredCalls()
{
	_Internal::g_mDeferredCalls.clear();
}

void ASGF::RemovePendingDeferredCall(DeferredCallHandle nHandle)
{
	_Internal::g_mDeferredCalls.erase(nHandle);
}

void ASGF::_Internal::ProcessDeferredCalls()
{
	std::erase_if(g_mDeferredCalls, [](std::pair<const DeferredCallHandle, T_DeferredCall>& obj)
		{
			if (obj.second.timer.Elapsed())
			{
				obj.second.hFunc();
				g_qFreedHandles.push(obj.first);
				return true;
			}
			return false;
		});
}
