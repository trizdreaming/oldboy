#include "stdafx.h"
#include "RMmacro.h"
#include "RMwellRandom.h"

CRMwellRandom::CRMwellRandom(void)
{
	m_WellIndex = 0;

	srand((unsigned long)time(NULL));

	for(int i = 0; i < 16; ++i)
	{
		m_WellState[i] = rand();
	}
}

CRMwellRandom::~CRMwellRandom(void)
{

}

unsigned long CRMwellRandom::WELLRNG512(void)
{
	unsigned long a, b, c, d;

	a = m_WellState[m_WellIndex];
	c = m_WellState[(m_WellIndex + 13) & 15];
	b = a ^ c ^ (a << 16) ^ (c << 15);
	c = m_WellState[(m_WellIndex + 9) & 15];
	c ^= (c >> 11);
	a = m_WellState[m_WellIndex] = b ^ c;
	d = a ^ ((a << 5) & 0xDA442D20UL);
	m_WellIndex = (m_WellIndex + 15) & 15;
	a = m_WellState[m_WellIndex];
	m_WellState[m_WellIndex] = a ^ b ^ d ^ (a << 2) ^ (b << 18) ^ (c << 28);

	return m_WellState[m_WellIndex];
}

unsigned long CRMwellRandom::WellRand(int r)
{
	return WELLRNG512() % r;
};

// 사이 값 랜덤
unsigned long CRMwellRandom::WellRandom(int nMin, int nMax)
{
	return (nMin + WellRand(nMax - nMin + 1));
}