#include <iostream>
#ifdef _WIN32
	#include <windows.h>
#else
	#include <unistd.h>
#endif
using namespace std;

int main(int argc, char** argv)
{

#ifdef _WIN32
        Sleep(3000);
#else
        usleep(100);
#endif
    cout << "hello world!" << endl; 
    return 0;
}
