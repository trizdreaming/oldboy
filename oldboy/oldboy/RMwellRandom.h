#pragma once

//sm9: 왜 랜덤을 따로 이렇게 가져와서 사용했지? 보통 이런 게임은 그냥 시스템 rand() 써도 됨
//더 정확한 랜덤을 쓰고 싶으면 http://en.wikipedia.org/wiki/Mersenne_twister 

class CRMwellRandom
{
	SINGLETON(CRMwellRandom);
private:
	CRMwellRandom(void);
	~CRMwellRandom(void);

public:
	unsigned long WELLRNG512(void);
	unsigned long WellRand(int r);
	unsigned long WellRandom(int nMin, int nMax);

private:
	unsigned long m_WellState[16];
	unsigned long m_WellIndex;
};
