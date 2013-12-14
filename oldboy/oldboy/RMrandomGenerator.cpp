#include "stdafx.h"
#include "RMmacro.h"
#include "RMrandomGenerator.h"

CRMrandomGenerator::CRMrandomGenerator(void) :
	m_Index(0)
{
	m_BitPow_31 = 1 << 31;
	ZeroMemory(&m_MTState, sizeof(m_MTState));
	Initialize();
}

CRMrandomGenerator::~CRMrandomGenerator(void)
{

}

void CRMrandomGenerator::Initialize()
{
	srand((unsigned long)time(NULL));
	m_MTState[0] = rand();

	for ( UINT i = 1 ; i < MAX_RANDOM_LENGTH ; ++i )
	{
		m_MTState[i] = (1812433253 * (m_MTState[i-1]^(m_MTState[i-1] >> 30)) + i) & BIT_MASK_32;
	}
};

void CRMrandomGenerator::Generate()
{
	for ( UINT i = 0 ; i < MAX_RANDOM_LENGTH ; ++i )
	{
		UINT temp = (m_MTState[i] & m_BitPow_31) + (m_MTState[(i + 1) % MAX_RANDOM_LENGTH]) & (m_BitPow_31 - 1);
		m_MTState[i] = m_MTState[ (i + 397) % MAX_RANDOM_LENGTH ] ^ ( temp >> 1 );

		if ( temp % 2 )
		{
			m_MTState[i] ^= 2567483615;
		}
	}
}

UINT CRMrandomGenerator::GetRandom()
{
	if ( m_Index == 0 )
	{
		Generate();
	}
	
	UINT result = m_MTState[m_Index];
	result ^= result >> 11;
	result ^= (result << 7) & 2636928640;
	result ^= (result << 15) & 4022730752;
	result ^= result >> 18;
	m_Index = (m_Index + 1) % MAX_RANDOM_LENGTH;
	
	return result;
}

// 사이 값 랜덤
UINT CRMrandomGenerator::GetRandom(UINT nMin, UINT nMax)
{
	return static_cast<UINT>(nMin + (static_cast<double>(GetRandom()) / UINT_MAX ) * (nMax - nMin + 1));
}
