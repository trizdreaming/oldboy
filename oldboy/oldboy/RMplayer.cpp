﻿#include "stdafx.h"
#include "RMmacro.h"
#include "RMplayer.h"
#include "RMsound.h"

CRMplayer::CRMplayer(void) :
	m_PrevIsCombo(false),
	m_HP(PLAYER_HP_MAX),
	m_MP(0),
	m_IsItemBoostOn(false)
{
	ZeroMemory( &m_Count, sizeof(m_Count) );
}

CRMplayer::~CRMplayer(void)
{
}

void CRMplayer::Init()
{
	ZeroMemory( &m_Count, sizeof(m_Count) );
	m_IsItemBoostOn = false;
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
		if ( m_Count[COUNT_COMBO] == 50 )
		{
			CRMsound::GetInstance()->PlayEffectTier(SOUND_EFFECT_PLAY_50_COMBO);
		}
		else if ( m_Count[COUNT_COMBO] == 100 )
		{
			CRMsound::GetInstance()->PlayEffectTier(SOUND_EFFECT_PLAY_100_COMBO);
		}
	}
}

void CRMplayer::AddEvent( JudgeType judgeEventType )
{
	switch ( judgeEventType )
	{
	case JUDGE_PERFECT:
		++m_Count[COUNT_PERFECT];
		m_Count[COUNT_SCORE] += SCORE_EACH_PERFECT * (m_IsItemBoostOn ? 3 : 1);
		m_MP += 18;
		
		if( m_MP > m_HP * PLAYER_HP_MP_RATE )
		{
			m_MP = m_HP * PLAYER_HP_MP_RATE;
		}
		CalcCombo();
		break;
	case JUDGE_GOOD:
		++m_Count[COUNT_GOOD];
		m_Count[COUNT_SCORE] += SCORE_EACH_GOOD * (m_IsItemBoostOn ? 2 : 1);
		m_MP += 12;
		
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

void CRMplayer::SubHP()
{
	if ( m_HP > 20 )
	{
		m_HP = m_HP - 5;
	}
}
