#include <iostream>
#ifdef _WIN32
	#include <windows.h>
#else
	#include <unistd.h>
#endif
#include "datastruct/BigDigit.h"
#include "utils/RAIIWrapper.h"
#include "gtest/gtest.h"

#include "CLI/CLI.hpp"
using namespace std;

void testRAII();



int main(int argc, char** argv)
{
	//CLI::App app;
	//CLI11_PARSE(app, argc, argv);


	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
#ifdef _MSC_VER
	cout << "Window MSC_VER :" << _MSC_VER << std::endl;
#endif
	
	testRAII();
#ifdef _WIN32
	Sleep(300000);
#else
	usleep(100);
#endif

    cout << "hello world!" << endl; 
    return 0;
}

/**
 * 测试RAII，必须是指针变量
 */
void testRAII() {
	CFloat* x = new CFloat("2.33333");
	RAIIWrapper<CFloat> cf(x);

}



