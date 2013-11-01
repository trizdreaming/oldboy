#include "stdafx.h"
#include "RMplayer.h"


CRMplayer::CRMplayer(void) :
	m_PerfectCount(0),
	m_GoodCount(0),
	m_MissCount(0),
	m_ComboCount(0),
	m_ScoreCount(0),
	m_PrevIsCombo(false)
{
}


CRMplayer::~CRMplayer(void)
{
}

void CRMplayer::CalcCombo()
{
	if ( m_PrevIsCombo == false )
	{
		m_ComboCount = 1;
		m_PrevIsCombo = true;
	}
	else
	{
		++m_ComboCount;
		m_ScoreCount += m_ComboCount;
	}
}

void CRMplayer::AddEvent( JudgeType judgeEventType )
{
	switch ( judgeEventType )
	{
	case JUDGE_PERFECT:
		++m_PerfectCount;
		m_ScoreCount += 5;
		CalcCombo();
		break;
	case JUDGE_GOOD:
		++m_GoodCount;
		m_ScoreCount += 3;
		CalcCombo();
		break;
	case JUDGE_MISS:
		m_ComboCount = 0;
		m_PrevIsCombo = false;
		++m_MissCount;
		break;
	default:
		break;
	}
}

UINT CRMplayer::GetCount( CountType countType )
{
	UINT count = 0;

	switch ( countType )
	{
	case PERFECT_COUNT:
		count = m_PerfectCount;
		break;
	case GOOD_COUNT:
		count = m_GoodCount;
		break;
	case MISS_COUNT:
		count = m_MissCount;
		break;
	case COMBO_COUNT:
		count = m_ComboCount;
		break;
	case SCORE_COUNT:
		count = m_ScoreCount;
		break;
	default:
		break;
	}

	return count;
}

void CRMplayer::SetCount( CountType countType, UINT count )
{
	switch ( countType )
	{
	case PERFECT_COUNT:
		m_PerfectCount = count;
		break;
	case GOOD_COUNT:
		m_GoodCount = count;
		break;
	case MISS_COUNT:
		m_MissCount = count;
		break;
	case COMBO_COUNT:
		m_ComboCount = count;
		break;
	case SCORE_COUNT:
		m_ScoreCount = count;
		break;
	default:
		break;
	}
}
