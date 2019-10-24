#include "BaseTest.h"

int Foo(int a, int b)
{
	if (a == 0 || b == 0)
	{
		throw "don't do that";
	}
	int c = a % b;
	if (c == 0)
		return b;
	return Foo(b, c);
}

int Abs(int x)
{
	return x > 0 ? x : -x;
}

TEST(FooTest, HandleNoneZeroInput)
{
	EXPECT_EQ(2, Foo(4, 10));
	EXPECT_EQ(6, Foo(30, 18));
}

TEST(IsAbsTest, HandlerTrueReturn)
{
	ASSERT_FALSE(Abs(1) == 1) << "Abs(1)=1"; //ASSERT_TRUE期待结果是true,operator<<输出一些自定义的信息
	ASSERT_TRUE(Abs(-1) == 1) << "Abs(-1)=1";
	ASSERT_FALSE(Abs(-2) == -2); //期待结果是false
	ASSERT_EQ(Abs(1), Abs(-1));
	ASSERT_NE(Abs(-1), 0);
	ASSERT_LT(Abs(-1), 2);
	ASSERT_GT(Abs(-1), 0);
	ASSERT_LE(Abs(-1), 2);
	ASSERT_GE(Abs(-1), 0);
}

/**
 * RAII资源释放
 */
void testRAII()
{
	CFloat *x = new CFloat("2.33333");
	RAIIWrapper<CFloat> cf(x);
}

void testIoPut()
{
	string inputStr;
	while (cin >> inputStr)
	{
		if (inputStr != "*")
		{
			string cpStr = "c++";
			char a[3];
			a[0] = 'a';
			a[1] = 'b';
			a[2] = '\0';
			char *b = "ab";
			printf("a is %s , b is %s\n", a, b);
			printf("c++ string is \n", cpStr.c_str());
			cout << inputStr << endl;
		}
		else
		{
			return;
		}
	}
}

#ifdef _WIN64
void testDeltaUs()
{
	LARGE_INTEGER cpuFreq;
	double startUs = getStartMicroTime(cpuFreq);
	Sleep(1);
	double endUs = getEndMicroTime();
	double deltaUs = (((endUs - startUs) * 1000.0f) / cpuFreq.QuadPart);
	cout << deltaUs * 1000 << " us" << endl;
}
#endif

#ifdef linux
void testRedis()
{
	CRedisConn *redisConn = new CRedisConn("127.0.0.1", 6380, "123456", 0);
	struct timeval tv = {1, 0};
	vector<string> cmdVc;
	for (int i = 0; i < 50000; i++)
	{
		string cJson = "{zzzz}";
		string cmdStr = "set k" + intToString(i) + " " + cJson;
		cmdVc.push_back(cmdStr);
	}
	for (int k = 0; k < 5000; k++)
	{
		vector<string> rspVc;
		vector<bool> rspStatusVc;
		unsigned long long start = getCurrentMilliTime();
		redisConn->pipeline_process(tv, cmdVc, rspVc, rspStatusVc);
		unsigned long long end = getCurrentMilliTime();
		cout << "50000[Set Op] , Cost time is " << end - start << "ms" << endl;
		csleep(20000);
	}
}
#endif

void googleTest(int argc, char **argv)
{
	//GoogleTest
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
}