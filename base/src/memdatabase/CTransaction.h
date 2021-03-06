#pragma once

#include "CResource.h"
#include "MemoryStack.h"

class CTransaction;

//////////////////////////////////////////////////////////////////////////
///CTransactionSavePoint是在一个事务中的保存点。使用这个保存点，可以实现
///事务的部分回滚
//////////////////////////////////////////////////////////////////////////
class CTransactionSavePoint:public CResource
{
public:
	CTransactionSavePoint(void)
	{
		ref=NULL;
	}
/*
	///构造函数
	///@param	pTransaction	要创建savepoint的transaction
	CTransactionSavePoint(CTransaction *pTransaction);
*/
	~CTransactionSavePoint(void);

	///完成提交
	virtual void commit(void)
	{
	}

	///完成滚回
	virtual void rollback(void)
	{
	}

	///与另一个资源合并
	///@param	pResource	要合并的另一个资源
	///@return	RESOURCE_MERGE_OK表示合并成功，
	///			RESOURCE_MERGE_FAIL_THIS表示本条合并失败，但是还可以尝试其他的
	///			RESOURCE_MERGE_FAIL_ALL表示合并全部失败，其他的也不用尝试了
	virtual int merge(CResource *pResource)
	{
		return RESOURCE_MERGE_FAIL_ALL;
	}
	
	///申请构造函数
	///@param	pTransaction	要创建savepoint的transaction
	static CTransactionSavePoint* alloc(CTransaction *pTransaction);
	
	///释放函数
	virtual void free(void);

	///是否控制资源，目前只有savepoint是控制资源
	///@return	true表示是，false表示否
	virtual bool isControl(void)
	{
		return true;
	}
private:
	CTransaction *m_Transaction;
	static CMemoryStack<CTransactionSavePoint> resourceList;
};


/////////////////////////////////////////////////////////////////////////
///CTransaction是一个事务，可以挂接一批资源，最后同意提交或滚回
///CTransaction继承了CResource，可以实现层次性的事务管理，即一个CTransaction
///中的一个CResource可以也是一个CTransaction
/////////////////////////////////////////////////////////////////////////
class CTransaction : public CResource, protected vector<CResource *>
{
public:
	friend class CTransactionSavePoint;

	//构造方法
	CTransaction(void);

	///析构方法
	virtual ~CTransaction(void);
	
	///在本事务中加入一个资源，注意，要加入的资源必须在外部创建，
	///但是由CTransaction负责删除
	///@param	pResource	需要加入的资源
	void addResource(CResource *pResource)
	{
		if (isMerge) {
			if (mergeBack(size(), pResource, false))
			{
				///合并成功，那就不用加了
				pResource->free();
			}
			else
			{
				///合并不成功，那就要加了
				push_back(pResource);
			}
		}
		else {
			push_back(pResource);
		}
	}

	///完成提交
	virtual void commit(void);
	
	///完成滚回
	virtual void rollback(void);
	
	///与另一个资源合并
	///@param	pResource	要合并的另一个资源
	///@return	RESOURCE_MERGE_OK表示合并成功，
	///			RESOURCE_MERGE_FAIL_THIS表示本条合并失败，但是还可以尝试其他的
	///			RESOURCE_MERGE_FAIL_ALL表示合并全部失败，其他的也不用尝试了
	virtual int merge(CResource *pResource)
	{
		return RESOURCE_MERGE_FAIL_THIS;
	}
	virtual void setIsMerge(bool isMerge);

	///回滚到指定的位置，如果没有指定过此位置，则相当于全部rollback，
	///本保存点将继续保留，反复使用
	///@param	pSavePoint	要回滚到的保存点
	virtual void rollbackToSavePoint(CTransactionSavePoint *pSavePoint);

private:
	///设立回滚点，主要要加入的保存点必须在外部创建，
	///但是由CTransaction负责删除
	///@param	pSavePoint	要设立的保存点
	virtual void setSavePoint(CTransactionSavePoint *pSavePoint);

	///尝试与前面的资源合并
	///@param	pos	指向可以合并的最后一个资源后的一个资源的下标
	///@param	pResource	要被合并的资源
	///@param	forceMerge	是否强制合并，true表示即使有资源表示全部失败，也还要继续尝试合并
	///@return	true表示已经被合并了，false表示没有被合并
	bool mergeBack(int pos,CResource *pResource,bool forceMerge)
	{
		for (pos--;pos>=0;pos--)
		{
			if (at(pos)->getRef()==NULL)
			{
				if (!forceMerge)
				{
					return false;
				}
				else
				{
					continue;
				}
			}
			if (at(pos)->getRef()!=pResource->getRef())
			{
				continue;
			}
			switch (at(pos)->merge(pResource))
			{
			case RESOURCE_MERGE_OK:
				///合并成功
				return true;
			case RESOURCE_MERGE_FAIL_THIS:
				///这个没有合并成功，应当尝试下一个
				break;
			case RESOURCE_MERGE_FAIL_ALL:
				///全部失败
				if (!forceMerge)
				{
					//不用再试了
					return false;
				}
				break;
			}
		}
		return false;
	}

	///已经设立的保存点数量
	int m_SavePointCount;
	bool isMerge;
};
