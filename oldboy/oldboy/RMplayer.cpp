#include "stdafx.h"
#include "RMplayer.h"


CRMplayer::CRMplayer(void)
{
}


CRMplayer::~CRMplayer(void)
{
}

void CRMplayer::SetCount( CountType countType, UINT score /*= 1*/ )
{
	switch ( countType )
	{
	case PERFECT_COUNT:
		m_PerfectCount = score;
		break;
	case GOOD_COUNT:
		m_GoodCount = score;
		break;
	case MISS_COUNT:
		m_MissCount = score;
		break;
	case COMBO_COUNT:
		m_ComboCount = score;
		break;
	case SCORE_COUNT:
		m_ScoreCount = score;
		break;
	case NO_COUNT:
		break;
	default:
		break;
	}
}

UINT CRMplayer::GetCount( CountType countType )
{
	switch ( countType )
	{
	case PERFECT_COUNT:
		return m_PerfectCount;
	case GOOD_COUNT:
		return m_GoodCount;
	case MISS_COUNT:
		return m_MissCount;
	case COMBO_COUNT:
		return m_ComboCount;
	case SCORE_COUNT:
		return m_ScoreCount;
	case NO_COUNT:
		break;
	default:
		break;
	}

	return 0;
}
