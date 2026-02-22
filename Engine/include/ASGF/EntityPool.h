#pragma	once
#include <map>
#include <functional>
#include <queue>
#include <cassert>

#define EntId_NULL -1
using EntId = int;

class EntityPool;

class EntityBase
{
public:
	EntId GetId();
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void OnDestroy() {};
	void DeleteThis(int delay = -1, bool bSuppressCallback = false);
	EntityPool* GetPool();

protected:
	EntityBase() = default;
private:
	EntityPool* m_pPool = nullptr;
	EntId m_nId = -1;

	friend class EntityPool;
	void _SetId(EntId nId);
};

class EntityPool
{
private:
	EntityPool& Get();
public:
	// Despite being a singleton, the constructor is public if the user wants to use multiple entity managers for different entity "categories"
	EntityPool() = default;
	~EntityPool();

	template <typename T> requires std::is_base_of_v<EntityBase, T>
	EntId CreateEntity(std::function<T*()> hConstructorLambda);

	EntId AddEntity(EntityBase* pNewEntity);

	// delay in milliseconds. A delay of 0 will delete on the next frame
	void DestroyEnt(EntId nId, int delay = -1, bool bSuppressCallback = false);

	void ClearEnts(bool bSuppressCallbacks = false);
	
	EntityBase& GetEntity(EntId nId);

	template <typename T> requires std::is_base_of_v<EntityBase, T>
	T& GetEntity(EntId nId);

	void Update();
	void Render();

private:
	std::map<EntId, EntityBase*> m_mEntities;
	std::queue<EntId> m_qFreeIDs;
	bool m_bOverflowed = false;
};

template<typename T> requires std::is_base_of_v<EntityBase, T>
inline EntId EntityPool::CreateEntity(std::function<T* ()> hConstructorLambda)
{
	T* newEnt = hConstructorLambda();
	AddEntity(newEnt);
}

template <typename T> requires std::is_base_of_v<EntityBase, T>
inline T& EntityPool::GetEntity(EntId nId)
{
	assert(m_mEntities.contains(nId));
	return dynamic_cast<T&>(*m_mEntities.at(nId));
}
