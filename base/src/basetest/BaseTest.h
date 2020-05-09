#pragma once

#include "platform.h"
#include "BigDigit.h"
#include "BaseUtils.h"
#ifdef linux
#include "HiredisUtil.h"
#endif
#include "gtest/gtest.h"
#include "Child.h"

void test();
void testRAII();
void testIoPut();
void testConst();
void googleTest(int argc, char** argv);

#ifdef _WIN64
void testDeltaUs();
#endif

#ifdef linux
void testRedis();
#endif


void testClass();
void testAllocator();