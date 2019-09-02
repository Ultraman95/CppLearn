#pragma once

template<class T>
class RAIIWrapper
{
public:
	RAIIWrapper(T* p) :ptr(p) {}

	virtual ~RAIIWrapper()
	{
		if (ptr != NULL)
		{
			delete ptr;
			ptr = NULL;
		}
	}
private:
	T* ptr;
};