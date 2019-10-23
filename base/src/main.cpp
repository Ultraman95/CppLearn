#include "platform.h"
#include "BigDigit.h"
#include "BaseUtils.h"
#include "gtest/gtest.h"

void test();
void testRAII();
void testIoPut();
#ifdef _WIN64
//void testDeltaUs();
#endif
void googleTest(int argc, char** argv);


int main(int argc, char** argv)
{
	printCV();
    csleep(300);
	return 0;
}


void test() {
	//testRAII();
}

/**
 * RAII资源释放
 */
void testRAII() {
	CFloat* x = new CFloat("2.33333");
	RAIIWrapper<CFloat> cf(x);

}

void testIoPut(){
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
        }else{
			return;
        }
    }
}

#ifdef _WIN64
/*void testDeltaUs(){
    LARGE_INTEGER cpuFreq;
    double startUs = getStartMicroTime(cpuFreq);
    Sleep(1);
    double endUs = getEndMicroTime();
    double deltaUs = (((endUs - startUs) * 1000.0f) / cpuFreq.QuadPart);
    cout << deltaUs*1000 << " us" << endl;
}*/
#endif

void googleTest(int argc, char** argv){
	//GoogleTest
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
}



