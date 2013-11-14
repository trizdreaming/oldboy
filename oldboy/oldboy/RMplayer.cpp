#include "stdafx.h"
#include "oldboy.h"
#include "RMplayer.h"


CRMplayer::CRMplayer(void) :
	m_PrevIsCombo(false),
	m_HP(PLAYER_HP_MAX)
{
	ZeroMemory( m_Count, sizeof(m_Count) );
}


CRMplayer::~CRMplayer(void)
{
}

void CRMplayer::CalcCombo()
{
	if ( m_PrevIsCombo == false )
	{
		m_Count[COUNT_COMBO] = 1;
		m_PrevIsCombo = true;
	}
	else
	{
		m_Count[COUNT_SCORE] += ++m_Count[COUNT_COMBO];
	}
}

void CRMplayer::AddEvent( JudgeType judgeEventType )
{
	switch ( judgeEventType )
	{
	case JUDGE_PERFECT:
		++m_Count[COUNT_PERFECT];
		m_Count[COUNT_SCORE] += 5;
		CalcCombo();
		break;
	case JUDGE_GOOD:
		++m_Count[COUNT_GOOD];
		m_Count[COUNT_SCORE] += 3;
		CalcCombo();
		break;
	case JUDGE_MISS:
		m_Count[COUNT_COMBO] = 0;
		m_PrevIsCombo = false;
		++m_Count[COUNT_MISS];
		break;
	default:
		break;
	}
}

UINT CRMplayer::GetCount( CountType countType ) const
{
	return m_Count[countType];
}

void CRMplayer::SetCount( CountType countType, UINT count )
{
	m_Count[countType] = count;
}
