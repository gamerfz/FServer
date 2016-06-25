/***********************************************************************
*FileName	:  PoolObject
*Author		:  fz
*Date		:  2016.4.9
*Description:  对象池 
	
	由多个对象集构成,初始化为一个对象集,每个对象集,有相同的大小的对象成员
	
	使用时注意需要手动处理脏数据
************************************************************************/
#pragma once

template<class T>
class ObjectPool
{
private:
	/*成员对象*/
	struct Object
	{
		T			obj;            //成员  
		Object*		next;			//向下的指针
		Object*		pre;			//向上的指针
		bool		isAlloc;
	};
	/*对象集*/
	struct Objects
	{
		Object*		curObj;			//当前对象
		Objects*	nextObjs;		//下个对象集
	};

	int				m_maxObjCnt;		//对象集中对象总数量
	int				m_objCnt;			//已分配对象数量
	int				m_objsCnt;			//对象集数量	
	Object*			m_unusedObjs;		//可用对象列表
	Objects*		m_objs;				//对象集
public:
	ObjectPool(void) : m_objs(NULL), m_unusedObjs(NULL){}
	virtual ~ObjectPool(void){}

	int	GetAllocatedSize(){ return m_objCnt; }
	int	GetPoolSize(){ return m_maxObjCnt * m_objsCnt; }
	bool IsCreated(){ return m_unusedObjs != NULL; }

	virtual bool Create(unsigned int maxCnt)
	{
		m_maxObjCnt = maxCnt;
		m_objsCnt = 1;

		m_objs = new Objects;
		m_objs->nextObjs = NULL;
		m_objs->curObj = new Object[m_maxObjCnt];

		//关联对象成员
		for (int i = 0; i < m_maxObjCnt; i++)
		{
			if (i > 0)
			{
				m_objs->curObj[i].pre = &m_objs->curObj[i - 1];
				m_objs->curObj[i - 1].next = &m_objs->curObj[i];
			}
			m_objs->curObj[i].isAlloc = false;
		}
		m_objs->curObj[0].pre = NULL;
		m_objs->curObj[m_maxObjCnt - 1].next = NULL;

		m_unusedObjs = m_objs->curObj;
		m_objCnt = 0;
		return true;
	}

	virtual void Destroy()
	{
		while (m_objs)
		{
			if (m_objs->curObj)
			{
				delete[] m_objs->curObj;
				m_objs->curObj = NULL;
			}

			Objects* pOld = m_objs;
			m_objs = m_objs->nextObjs;
			delete pOld;
		}
	}

	virtual T* Alloc()
	{
		if (!m_unusedObjs)
		{
			Objects* pSet = new Objects;
			pSet->nextObjs = m_objs;
			pSet->curObj = new Object[m_maxObjCnt];

			for (int i = 0; i < m_maxObjCnt; i++)
			{
				if (i > 0)
				{
					pSet->curObj[i].pre = &pSet->curObj[i - 1];
					pSet->curObj[i - 1].next = &pSet->curObj[i];
				}
				pSet->curObj[i].isAlloc = false;
			}
			pSet->curObj[0].pre = NULL;
			pSet->curObj[m_maxObjCnt - 1].next = NULL;

			m_unusedObjs = pSet->curObj;
			m_objs = pSet;
			m_objsCnt++;
		}

		Object* pFreeObj;
		pFreeObj = m_unusedObjs;
		m_unusedObjs = m_unusedObjs->next;
		if (m_unusedObjs)
			m_unusedObjs->pre = NULL;

		pFreeObj->isAlloc = true;
		m_objCnt++;

		return (T*)&(pFreeObj->obj);
	}

	void Free(T* pElement)
	{
		Object* pObject = (Object*)pElement;

		if (!pObject->isAlloc)
			return;

		pObject->next = m_unusedObjs;
		pObject->pre = NULL;
		if (m_unusedObjs)
			m_unusedObjs->pre = pObject;
		m_unusedObjs = pObject;

		m_objCnt--;

		pObject->isAlloc = false;
	}
};




/*
//c11
#pragma once
#include <boost/pool/object_pool.hpp>
#include <memory>

using namespace std;
template<class obj_type>
class enable_obj_pool
{
	static boost::object_pool<obj_type> _pool;
public:
	static std::shared_ptr<obj_type> alloc()
	{
		//利用shared_ptr从对象池中获取构造一个对象,(构造函数,析构调用的方法),placeholders占位符配合bind,表示free方法必须有一个参数
		return std::shared_ptr<obj_type>(_pool.construct(), bind(&obj_type::free, std::placeholders::_1));
	}

	static void free(obj_type* o)
	{
		_pool.destroy(o);
	}
};

#define enable_obj_pool_entity(thing) boost::object_pool<thing> enable_obj_pool<thing>::_pool;*/
