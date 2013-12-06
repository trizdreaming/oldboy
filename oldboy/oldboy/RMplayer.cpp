#include "stdafx.h"
#include "RMplayer.h"


CRMplayer::CRMplayer(void) :
	m_PrevIsCombo(false),
	m_HP(PLAYER_HP_MAX),
	m_MP(0)
{
	ZeroMemory( m_Count, sizeof(m_Count) );
}

CRMplayer::~CRMplayer(void)
{
}

void CRMplayer::Init()
{
	ZeroMemory( m_Count, sizeof(m_Count) );
	m_PrevIsCombo = false;
	m_HP = PLAYER_HP_MAX;
	m_MP = 0;
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
		++m_Count[COUNT_COMBO];
		m_Count[COUNT_COMBO_SCORE] += m_Count[COUNT_MAX_COMBO];
		m_Count[COUNT_SCORE] += m_Count[COUNT_MAX_COMBO];

		if ( m_Count[COUNT_COMBO] > m_Count[COUNT_MAX_COMBO] )
		{
			m_Count[COUNT_MAX_COMBO] = m_Count[COUNT_COMBO];
		}
	}
}

void CRMplayer::AddEvent( JudgeType judgeEventType )
{
	switch ( judgeEventType )
	{
	case JUDGE_PERFECT:
		++m_Count[COUNT_PERFECT];
		m_Count[COUNT_SCORE] += SCORE_EACH_PERFECT;
		m_MP += 16;
		//
		//m_MP += 160;
		// 디버깅을 위한 테스트 모드 - 마나 무한대
		if( m_MP > m_HP * PLAYER_HP_MP_RATE )
		{
			m_MP = m_HP * PLAYER_HP_MP_RATE;
		}
		CalcCombo();
		break;
	case JUDGE_GOOD:
		++m_Count[COUNT_GOOD];
		m_Count[COUNT_SCORE] += SCORE_EACH_GOOD;
		m_MP += 8;
		//
		m_MP += 80;
		// 디버깅을 위한 테스트 모드 - 마나 무한대
		if( m_MP > m_HP * PLAYER_HP_MP_RATE )
		{
			m_MP = m_HP * PLAYER_HP_MP_RATE;
		}
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

void CRMplayer::AddHP( int hpUp )
{
	m_HP += hpUp;
	if ( m_HP > PLAYER_HP_MAX )
	{
		m_HP = PLAYER_HP_MAX;
	}
}
