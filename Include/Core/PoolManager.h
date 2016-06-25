/***********************************************************************
*FileName	:  PoolObject
*Author		:  fz
*Date		:  2016.4.9
*Description:  对象池管理类

	所有使用本池的管理类必须在首次使用前调用InitPool(),设置初始大小

	所有使用池的对象类必须继承PoolObject并实现OnReset回收脏数据

	出于应对大量玩家和效率的考虑,使用的是c11的unordered_map,如需要有序的map vecter list等可自行实现池管理类
************************************************************************/
#pragma once
#include <unordered_map>
#include "ObjectPool.h"

#define POOL_BASE_SIZE 100

class PoolObject
{
public:
	virtual ~PoolObject(){}
	virtual void OnReset() = 0;
};

template< class ObjectKey, class ObjectType >
class PoolManager : public ObjectPool< ObjectType >
{
	std::unordered_map<ObjectKey, ObjectType*> mObjects;
public:
	PoolManager();
	~PoolManager();

	void InitPool(int size = POOL_BASE_SIZE);
	ObjectType* AddObject(ObjectKey objectID);
	void RemoveObject(ObjectKey objectID);
	ObjectType* GetObject(ObjectKey objectID);

	std::unordered_map<ObjectKey, ObjectType*>& GetObjectMap(){ return mObjects; }
};

template< class ObjectKey, class ObjectType >
PoolManager< ObjectKey, ObjectType >::PoolManager()
{
}

template< class ObjectKey, class ObjectType >
PoolManager< ObjectKey, ObjectType >::~PoolManager()
{
}

template<class ObjectKey, class ObjectType >
void PoolManager< ObjectKey, ObjectType >::InitPool(int size /* = POOL_BASE_SIZE */)
{
	this->Create(size);
}

template< class ObjectKey, class ObjectType >
ObjectType* PoolManager< ObjectKey, ObjectType >::AddObject(ObjectKey objectID)
{
	auto it = mObjects.find(objectID);
	if (it != mObjects.end())
		return NULL;
	ObjectType* obj = this->Alloc();
	if (obj == NULL)
		return NULL;

	mObjects.insert(std::make_pair(objectID, obj));
	return obj;
}

template< class ObjectKey, class ObjectType >
ObjectType* PoolManager< ObjectKey, ObjectType >::GetObject(ObjectKey objectID)
{
	auto it = mObjects.find(objectID);
	if (it == mObjects.end())
		return NULL;
	return it->second;
}

template< class ObjectKey, class ObjectType >
void PoolManager< ObjectKey, ObjectType >::RemoveObject(ObjectKey objectID)
{
	auto it = mObjects.find(objectID);
	if (it == mObjects.end())
		return;

	if (it->second == NULL)
		return;

	it->second->OnReset();
	Free(it->second);
	mObjects.erase(it);
}