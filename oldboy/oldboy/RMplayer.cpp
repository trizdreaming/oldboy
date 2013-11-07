#include "stdafx.h"
#include "oldboy.h"
#include "RMplayer.h"


CRMplayer::CRMplayer(void) :
	m_PrevIsCombo(false)
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
		m_Count[COMBO_COUNT] = 1;
		m_PrevIsCombo = true;
	}
	else
	{
		m_Count[SCORE_COUNT] += ++m_Count[COMBO_COUNT];
	}
}

void CRMplayer::AddEvent( JudgeType judgeEventType )
{
	switch ( judgeEventType )
	{
	case JUDGE_PERFECT:
		++m_Count[PERFECT_COUNT];
		m_Count[SCORE_COUNT] += 5;
		CalcCombo();
		break;
	case JUDGE_GOOD:
		++m_Count[GOOD_COUNT];
		m_Count[SCORE_COUNT] += 3;
		CalcCombo();
		break;
	case JUDGE_MISS:
		m_Count[COMBO_COUNT] = 0;
		m_PrevIsCombo = false;
		++m_Count[MISS_COUNT];
		break;
	default:
		break;
	}
}

UINT CRMplayer::GetCount( CountType countType )
{
	return m_Count[countType];
}

void CRMplayer::SetCount( CountType countType, UINT count )
{
	m_Count[countType] = count;
}
