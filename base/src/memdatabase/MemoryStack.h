#pragma once
#include "platform.h"

/////////////////////////////////////////////////////////////////////////
///CMemoryStack<T>是一个类型T的以堆栈方式申请和释放的内存管理器。也就是说，
///类型T的申请和释放将使用这个类的alloc和free方法，而且，先alloc出去的，
///一定后free。这里的T必须有缺省的构造子，而且不能在内部再申请其他空间，
///其析构方法必须无事可做
/////////////////////////////////////////////////////////////////////////
template <class T> class CMemoryStack: public vector<T *>
{
private:
	int allocCount;
public:
	///构造函数
	CMemoryStack(void)
	{
		allocCount=0;
	}

	///申请一个
	///@return	申请得到的对象
	T *alloc(void)
	{
		if (allocCount==vector<T *>::size())
		{
			push_back(new T);
		}
		return vector<T *>::at(allocCount++);
	}

	///释放一个
	///@param	p	要释放的对象
	void free(T *p)
	{
		allocCount--;
	}
	
	///释放所有对象
	void clear(void)
	{
		allocCount=0;
	}
}; 
