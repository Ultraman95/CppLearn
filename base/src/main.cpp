#include "platform.h"
#include "BigDigit.h"
#include "BaseUtils.h"
#include "gtest/gtest.h"

void test();
void testRAII();
void testIoPut();
void googleTest(int argc, char** argv);


int main(int argc, char** argv)
{
	printCV();
	test();
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

void googleTest(int argc, char** argv){
	//GoogleTest
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
}



