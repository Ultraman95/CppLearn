#pragma once

#include "platform.h"

#define CMAX 1024

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

struct minIndex {
    string day;
    int index;
};

//获取当前时间的毫秒数
unsigned long long getCurrentTimeMsec();

//单位是秒
void getIndexMinute(unsigned long long timeSec,minIndex &mIndex);

//单位是毫秒
void sleep(int milliseconds);

//打印编译器的版本
void printCV();

string intToString(int v);




