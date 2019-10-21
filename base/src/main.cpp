#include <iostream>
#ifdef _WIN32
	#include <windows.h>
	#include <direct.h>
#else
	#include <unistd.h>
#endif
#include "datastruct/BigDigit.h"
#include "utils/RAIIWrapper.h"
#include "gtest/gtest.h"

#include "CLI/CLI.hpp"

#include <stdio.h>
using namespace std;

#define MKDIR(a) _mkdir((a))

void test();
void testRAII();
void testWriteFile();



int main(int argc, char** argv)
{
	//CLI::App app;
	//CLI11_PARSE(app, argc, argv);
	//customSprintf(12, 8, 2.31000045067);

	//GoogleTest
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
#ifdef _MSC_VER
	cout << "Window MSC_VER :" << _MSC_VER << std::endl;
#endif
	
#ifdef _WIN32
	Sleep(300000);
#else
	usleep(100);
#endif

    cout << "hello world!" << endl; 
    return 0;
}


void test() {
	testRAII();
	testWriteFile();
}

/**
 * RAII资源释放
 */
void testRAII() {
	CFloat* x = new CFloat("2.33333");
	RAIIWrapper<CFloat> cf(x);

}


void testWriteFile() {
	const char* dir = "../../data\\tick\\";  
	int a = MKDIR(dir);		//子目录无法自动创建
	const char* cc = "../../tt.csv";
	FILE *file = fopen(cc, "a+");
	if (file == NULL)
	{
		//fopen,a+会自动创建文件，但不会自动创建目录
	}
}

void testIOStream(){
	/*std::string inputStr;
    while (std::cin >> inputStr)
    {
        if (inputStr != "*")
        {
            std::string cpStr = "c++";
            char a[3];
            a[0] = 'a';
            a[1] = 'b';
            a[2] = '\0';
            char *b = "ab";     
            printf("a is %s , b is %s\n", a, b);
            printf("c++ string is \n", cpStr.c_str());
            std::cout << inputStr << std::endl;
        }else{
            printf("Exit (yes-0/no-1) :");
            int t = std::cin.get();
            if(t == 0){
                return 0;
            }
        }
    }*/
}



