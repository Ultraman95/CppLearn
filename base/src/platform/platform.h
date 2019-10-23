
#pragma once

#ifdef _WIN64 //x64支持_WIN32,_WIN64  x86只支持WIN32
#include <winsock2.h>
#include <time.h>
#include <windows.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif
#include <chrono>
#include <iostream>
#include <string>
#include "stdio.h"
#include <cmath>

using std::cin;
using std::cout;
using std::endl;
using std::string;