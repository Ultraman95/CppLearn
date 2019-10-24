#pragma once

#include "platform.h"
#include "BigDigit.h"
#include "BaseUtils.h"
#include "gtest/gtest.h"

void test();
void testRAII();
void testIoPut();
#ifdef _WIN64
void testDeltaUs();
#endif
void googleTest(int argc, char** argv);