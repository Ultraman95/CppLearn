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
	ASSERT_FALSE(Abs(1) == 1) << "Abs(1)=1"; //ASSERT_TRUE�ڴ������true,operator<<���һЩ�Զ������Ϣ
	ASSERT_TRUE(Abs(-1) == 1) << "Abs(-1)=1";
	ASSERT_FALSE(Abs(-2) == -2); //�ڴ������false
	ASSERT_EQ(Abs(1), Abs(-1));
	ASSERT_NE(Abs(-1), 0);
	ASSERT_LT(Abs(-1), 2);
	ASSERT_GT(Abs(-1), 0);
	ASSERT_LE(Abs(-1), 2);
	ASSERT_GE(Abs(-1), 0);
}

/**
 * RAII��Դ�ͷ�
 */
void testRAII()
{
	CFloat* x = new CFloat("2.33333");
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
			char* b = "ab";
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

void googleTest(int argc, char** argv)
{
	//GoogleTest
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
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
	CRedisConn* redisConn = new CRedisConn("127.0.0.1", 6380, "123456", 0);
	struct timeval tv = { 1, 0 };
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


void testConst() {
	const char* p0 = "p0";	//ָ��pָ��������ǳ��������ɸı�
	char* const p1 = "p1";	//ָ�뱾����һ�����������ɸı�
	const char* const p2 = "p2";	//ָ�뱾���ָ������ݶ��ǳ������������Ըı�

	{
		const int a = 9;
		int* b = (int*)&a;	//&a����a��ʶ������ռ��ˣ�����bָ���˸ÿռ䣬
							//����ͨ��*b���������ַ�����ǲ���ͨ��a������
		*b = 3;
		cout << a << "------" << *b << endl;
		cout << &a << "------" << b << endl;
	}

	{
		int a = 8;
		int b = 7;
		const int* c = &a;
		//*c = 7;	//Error
		a = 10;
		cout << a << "------" << *c << endl;
		c = &b;
		cout << *c << endl;
	}

	{
		int a = 2;
		int b = 3;
		int* const c = &a;
		*c = 4;
		//c = &b;	//Error
		cout << a << endl;
	}

	//const�÷�
	//1.���峣��
	//2.��Ϊ�������ݣ����ֲ��ɱ���
	//3.��Ա�������棬�����˺��������޸��κγ�Ա������ͬʱҲ��������κη�const����
}


void testClass() {
	int age = 23;
	Child* shilf = new Child("shilf", "china", "female", age);
	Teacher* ta = new Teacher();
}

void testAllocator() {
	long n{ 1 };
	/*
	allocator<string> alloc;
	auto const p = alloc.allocate(n);
	auto q = p;
	for (int i = 0; i < n; i++)
	{
		alloc.construct(q++, "zz");
	}

	while (q != p) {
		alloc.destroy(--q);
	}
	alloc.deallocate(p, n);
	cout << "destroy done !" << endl;

	//alloc.construct(q++); //���ַ���
	//alloc.construct(q++, 10, 'c');
	//cout << *p << endl;
	//cout << p[0] << endl;
	*/
	allocator<Child> calloc;
	auto const p1 = calloc.allocate(n);
	auto q1 = p1;
	int age = 23;
	Child x{ "shilf", "china", "female", age };
	calloc.construct(q1++, x);
	while (q1 != p1) {
		calloc.destroy(--q1);
	}
	calloc.deallocate(p1, n);
	cout << "destroy done !" << endl;

}

