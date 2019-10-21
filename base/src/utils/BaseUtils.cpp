#include "BaseUtils.h"

unsigned long long GetCurrentTimeMsec()
{
#ifdef _WIN32
    struct timeval tv;
    time_t clock;
    struct tm tm;
    SYSTEMTIME wtm;

    GetLocalTime(&wtm);
    tm.tm_year = wtm.wYear - 1900;
    tm.tm_mon = wtm.wMonth - 1;
    tm.tm_mday = wtm.wDay;
    tm.tm_hour = wtm.wHour;
    tm.tm_min = wtm.wMinute;
    tm.tm_sec = wtm.wSecond;
    tm.tm_isdst = -1;
    clock = mktime(&tm);
    tv.tv_sec = clock;
    tv.tv_usec = wtm.wMilliseconds * 1000;
    return ((unsigned long long)tv.tv_sec * 1000 + (unsigned long long)tv.tv_usec / 1000);
#else
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((unsigned long long)tv.tv_sec * 1000 + (unsigned long long)tv.tv_usec / 1000);
#endif
}


minIndex GetIndexMinute(unsigned long long timeSec) {
    time_t tick = (time_t)timeSec;
    struct tm *tx;
    tx = localtime(&tick);

    char dayStr[100] = { 0 };
    strftime(dayStr, 100, "%Y-%m-%d", tx);
    int minute = tx->tm_min;
    int hour = tx->tm_hour;
    int index = hour * 60 + minute;
    minIndex mIndex;
    mIndex.day = dayStr;
    mIndex.index = index;
    return mIndex;
}

/*
void customSprintf(int width, int decimals, double value) {
	char tmp[100];
	sprintf(tmp, "%*.*lf", width, decimals, value);
	//return tmp;
}
*/



