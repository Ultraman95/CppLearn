#pragma once

#include "platform.h"


//---------------RAII相关-------------

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


//---------------时间相关-------------

struct minIndex {
	string day;
	int index;
};

//获取当前时间的毫秒数，可以用来算毫秒差
unsigned long long getCurrentMilliTime();

//获取微秒差

#ifdef _WIN64
double getStartMicroTime(LARGE_INTEGER& cpuFreq);
double getEndMicroTime();
#endif

//单位是秒，计算这一秒在一天的哪一分钟里
void getSecIndexMin(unsigned long long timeSec, minIndex& mIndex);

//单位是毫秒
void csleep(int milliseconds);


long stringTimeToUnixTime(const char* tradingday, const char* updatetime);





//---------------String相关-------------

string intToString(int v);



//---------------一般相关-------------

//打印编译器的版本
void printCV();




