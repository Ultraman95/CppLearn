#include "BaseUtils.h"

unsigned long long getCurrentTimeMsec()
{
#ifdef _WIN64
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


void getIndexMinute(unsigned long long timeSec,minIndex &mIndex) {
    time_t tick = (time_t)timeSec;
    struct tm *tx;
    tx = localtime(&tick);

    char dayStr[100] = { 0 };
    strftime(dayStr, 100, "%Y-%m-%d", tx);
    int minute = tx->tm_min;
    int hour = tx->tm_hour;
    int index = hour * 60 + minute;
	mIndex.day = dayStr;
	mIndex.index = index;
}

string intToString(int v)
{
    char buf[32] = {0};
    snprintf(buf, sizeof(buf), "%u", v);
    string str = buf;
    return str;
}


void sleep(int milliseconds) {
#ifdef _WIN64
	Sleep(milliseconds);
#else
	usleep(milliseconds);
#endif
}

void printCV() {
#ifdef _MSC_VER
	cout << "Window MSC_VER :" << _MSC_VER << endl;
#endif
}

