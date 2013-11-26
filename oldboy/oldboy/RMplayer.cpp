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
		m_Count[COUNT_SCORE] += ++m_Count[COUNT_COMBO];

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
		m_Count[COUNT_SCORE] += 5; //SM9: 이런 상수나 리터럴들은 따로 빼는거 알지?
		m_MP += 16;
		if( m_MP > m_HP * 65 )
		{
			m_MP = m_HP * 65;
		}
		CalcCombo();
		break;
	case JUDGE_GOOD:
		++m_Count[COUNT_GOOD];
		m_Count[COUNT_SCORE] += 3;
		m_MP += 8;
		if( m_MP > m_HP * 65 )
		{
			m_MP = m_HP * 65;
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
	//SM9: 열라 위험해질 수 있는 코드다.. COUNT_MAX와 MAX_COUNT가 다르다면?
	// m_Count 아래의 멤버 변수들을 덮어쓰게 된다... ㅎㄷㄷ
	m_Count[countType] = count;
}
