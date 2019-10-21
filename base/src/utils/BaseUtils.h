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
    char * day;
    int index;
};

unsigned long long GetCurrentTimeMsec();

minIndex GetIndexMinute(unsigned long long timeSec);

//单位是毫秒
void sleep(int milliseconds);

void printCV();


