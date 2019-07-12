#ifndef TICK_TO_KLINE_H_
#define TICK_TO_KLINE_H_

#include <stdint.h>
#include <vector>
#include "utils.h"

#define max(a,b)    (((a) > (b)) ? (a) : (b))
#define min(a,b)    (((a) < (b)) ? (a) : (b))


typedef struct TickField {
	uint64_t		TimeStamp;				///ʱ���������
	double			LastPrice;
	uint64_t		OpenInterest;
	uint64_t		Volume;
	double			AskPrice;
	uint64_t		AskVolume;
	double			BidPrice;
	uint64_t		BidVolume;
} TickField;


typedef struct KlineField {
	uint64_t		TimeStamp;				///ʱ���������
	double			Open;
	double			High;
	double			Low;
	double			Close;
	double			Average;
	int				UpOrDown;
	uint64_t		InterOpenInterest;		///������ʼ�ĳֲ���
	uint64_t		InterVolume;			///������ʼ�ĳɽ���
	uint64_t		DeltaOpenInterest;
	uint64_t		DeltaVolume;
	double			DeltaCO;
    std::string     Day;
    int             minIndex;
} KlineField;


class KlineContainer 
{
private:
	bool flag = false;
	TickField lastTick;
	TickField currTick;

	//std::vector<KlineField> *Kline = nullptr;
	std::vector<KlineField> *kline3s = nullptr;
	std::vector<KlineField> *kline5s = nullptr;
	std::vector<KlineField> *kline10s = nullptr;
	std::vector<KlineField> *kline15s = nullptr;
    std::vector<KlineField> *kline60s = nullptr;

	void InsertTick(std::vector<KlineField> *, TickField &, int);

    KlineField *sendedField;

    char zz[CMAX];

public:
	KlineContainer();
	void InsertTick(TickField &);
};

#endif // !TICK_TO_KLINE_H_

