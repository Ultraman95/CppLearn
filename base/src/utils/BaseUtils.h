#pragma once

#include "platform.h"


//---------------RAII���-------------

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


//---------------ʱ�����-------------

struct minIndex {
	string day;
	int index;
};

//��ȡ��ǰʱ��ĺ���������������������
unsigned long long getCurrentMilliTime();

//��ȡ΢���

#ifdef _WIN64
double getStartMicroTime(LARGE_INTEGER& cpuFreq);
double getEndMicroTime();
#endif

//��λ���룬������һ����һ�����һ������
void getSecIndexMin(unsigned long long timeSec, minIndex& mIndex);

//��λ�Ǻ���
void csleep(int milliseconds);


long stringTimeToUnixTime(const char* tradingday, const char* updatetime);





//---------------String���-------------

string intToString(int v);



//---------------һ�����-------------

//��ӡ�������İ汾
void printCV();




