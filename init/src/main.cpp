#include <iostream>
#include "tick2kline.h"

using namespace std;

int main(int argc, char** argv)
{
    double price = 10;
    uint64_t volume = 1;
    uint64_t ins = 1;
    KlineContainer *kc = new KlineContainer();
    for (;;) {
        
        TickField t;
        t.AskPrice = price+ 1;
        t.BidPrice = price- 1;
        t.AskVolume = volume;
        t.BidVolume = volume;
        t.LastPrice = price;
        t.OpenInterest = volume;
        t.Volume = volume;
        t.TimeStamp = GetCurrentTimeMsec();
        kc->InsertTick(t);
        price += 1;
        volume += 1;
        ins += 1;
#ifdef _WIN32
        Sleep(3);
#else
        usleep(100);
#endif
    }

    cout << "hello world!" << endl; 
    return 0;
}
