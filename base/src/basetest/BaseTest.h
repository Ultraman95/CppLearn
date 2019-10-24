#pragma once

#include "platform.h"
#include "BigDigit.h"
#include "BaseUtils.h"
#ifdef linux
#include "HiredisUtil.h"
#endif
#include "gtest/gtest.h"

void test();
void testRAII();
void testIoPut();
#ifdef _WIN64
void testDeltaUs();
#endif
void googleTest(int argc, char** argv);
#ifdef linux
void testRedis();
#endif