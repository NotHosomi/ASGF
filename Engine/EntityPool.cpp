#include "include/ASGF/EntityPool.h"
#include <cassert>
#include "include/ASGF/DeferredCall.h"

#define MAX_ENTITIES 0xFFFF //65536

EntityPool& EntityPool::Get()
{
	static EntityPool instance;
	return instance;
}

EntId EntityBase::GetId()
{
	return m_nId;
}

void EntityBase::DeleteThis(int delay, bool bSuppressCallback)
{
	m_pPool->DestroyEnt(m_nId, delay, bSuppressCallback);
}

void EntityBase::_SetId(EntId nId)
{
	m_nId = nId;
}

EntId EntityPool::AddEntity(EntityBase* pNewEntity)
{
	assert(pNewEntity->m_pPool == nullptr);
	pNewEntity->m_pPool = this;

	EntId id;
	if (!m_bOverflowed)
	{
		static int next = 0;
		id = next;
		next++;
		++next;
		if (id == MAX_ENTITIES)
		{
			m_bOverflowed = true;
		}
	}
	else
	{
		assert(m_qFreeIDs.size() > 0 && "Too many entities. Ran out of IDs");
		id = m_qFreeIDs.front();
		m_qFreeIDs.pop();
	}
	pNewEntity->_SetId(id);
	m_mEntities.insert({ id, pNewEntity });
	return id;
}

void EntityPool::DestroyEnt(EntId nId, int delay, bool bSuppressCallback)
{
	assert(m_mEntities.contains(nId));
	EntityBase* e = m_mEntities.at(nId);
	if (delay < 0)
	{
		if (!bSuppressCallback)
		{
			e->OnDestroy();
		}
		delete e;
	}
	else if (delay == 0)
	{
		ASGF::DeferCall([e, bSuppressCallback]()
			{
				if (!bSuppressCallback)
				{
					e->OnDestroy();
				}
				delete e;
			}, delay);
	}
	m_mEntities.erase(nId);
	m_qFreeIDs.push(nId);
}

void EntityPool::ClearEnts(bool bSuppressCallbacks = false)
{
	if (!bSuppressCallbacks)
	{
		for (auto ent : m_mEntities)
		{
			ent.second->OnDestroy();
		}
	}
	m_mEntities.clear();
}

EntityBase& EntityPool::GetEntity(EntId nId)
{
	assert(m_mEntities.contains(nId));
	return *m_mEntities.at(nId);
}
