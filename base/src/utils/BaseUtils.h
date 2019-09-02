#pragma once

#ifdef _WIN32
#include <winsock2.h>
#include <time.h>
#include <windows.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif
#include <chrono>

#define CMAX 1024

struct minIndex {
    char * day;
    int index;
}; 

unsigned long long GetCurrentTimeMsec();

minIndex GetIndexMinute(unsigned long long timeSec);


