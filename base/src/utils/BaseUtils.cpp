#include "BaseUtils.h"

//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓时间相关↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓

unsigned long long getCurrentMilliTime()
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


void getSecIndexMin(unsigned long long timeSec, minIndex& mIndex) {
	time_t tick = (time_t)timeSec;
	struct tm* tx;
	tx = localtime(&tick);

	char dayStr[100] = { 0 };
	strftime(dayStr, 100, "%Y-%m-%d", tx);
	int minute = tx->tm_min;
	int hour = tx->tm_hour;
	int index = hour * 60 + minute;
	mIndex.day = dayStr;
	mIndex.index = index;
}

#ifdef _WIN64
double getStartMicroTime(LARGE_INTEGER& cpuFreq) {
	LARGE_INTEGER startTime;
	double rumTime = 0.0;
	QueryPerformanceFrequency(&cpuFreq);
	QueryPerformanceCounter(&startTime);
	return startTime.QuadPart;
}

double getEndMicroTime() {
	LARGE_INTEGER endTime;
	QueryPerformanceCounter(&endTime);
	return endTime.QuadPart;
}
#endif


void csleep(int milliseconds) {
#ifdef _WIN64
	Sleep(milliseconds);
#else
	usleep(milliseconds);
#endif
}

long stringTimeToUnixTime(const char* tradingday, const char* updatetime)
{
	if (tradingday == NULL || updatetime == NULL)
	{
		return 0;
	}
	struct tm tm;
	memset(&tm, 0, sizeof(tm));
	char cyear[5] = { "0" };
	char cmonth[3] = { "0" };
	char cday[3] = { "0" };
	char chour[3] = { "0" };
	char cmin[3] = { "0" };
	char csecd[3] = { "0" };

	if (strlen(tradingday) >= 8)
	{
		strncpy(cyear, tradingday, 4);
		strncpy(cmonth, tradingday + 4, 2);
		strncpy(cday, tradingday + 6, 2);
	}

	if (strlen(updatetime) >= 6)
	{
		strncpy(chour, updatetime, 2);
		strncpy(cmin, updatetime + 3, 2);
		strncpy(csecd, updatetime + 6, 2);
	}

	tm.tm_year = atoi(cyear);
	tm.tm_year -= 1900;
	tm.tm_mon = atoi(cmonth);
	tm.tm_mday = atoi(cday);
	tm.tm_mon--;
	tm.tm_hour = atoi(chour);
	tm.tm_min = atoi(cmin);
	tm.tm_sec = atoi(csecd);
	return mktime(&tm);
}

//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑时间相关↑↑↑↑↑↑↑↑↑↑↑↑↑↑



//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓String相关↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓


string intToString(int v)
{
	char buf[32] = { 0 };
	snprintf(buf, sizeof(buf), "%u", v);
	string str = buf;
	return str;
}


//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑String相关↑↑↑↑↑↑↑↑↑↑↑↑↑↑


//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓一般相关↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓

void printCV() {
#ifdef _MSC_VER
	cout << "Window MSC_VER :" << _MSC_VER << endl;
#else
	cout << "Linux Gcc" << endl;
#endif
}


//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑一般相关↑↑↑↑↑↑↑↑↑↑↑↑↑↑