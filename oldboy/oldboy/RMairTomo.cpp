#include "stdafx.h"
#include "RMairTomo.h"
#include "RMrandomGenerator.h"
#include "RMinput.h"
#include "RMsound.h"
#include "RMmacro.h"
#include "RMitemManager.h"
#include "RMplayer2P.h"


CRMairTomo::CRMairTomo(void)
{
	Initialize();
}


CRMairTomo::~CRMairTomo(void)
{
}

void CRMairTomo::Initialize()
{
	printConsole("AirTomo Initialized! \n");
	m_Mental = 15;
	m_KeyInputReadyTime = 0;
	m_KeyInputReadyType = WIDGET_NOTE_NORMAL_1;

	m_InputReadyList.clear();
	m_InputReadyType.clear();

	m_ReadyItem = 0;
	m_PerfectTime = 2260;
	m_IsStart = true;
}
void CRMairTomo::SetPerfectTime( UINT PerfectTime )
{
	if ( PerfectTime > 2400 )
	{
		m_PerfectTime = 2250;
	}
	else
	{
		m_PerfectTime = PerfectTime;
	}
	
}
void CRMairTomo::SetRandomJudge( UINT NextNoteTime, WidgetType NextNoteType , UINT BeforeNoteTime )
{
	m_IsStart = false;
	m_KeyInputReadyType = NextNoteType;
	//printConsole("virtual Player CALL SetRandomJudge! %d\n",NextNoteTime);
	int delayTime = NextNoteTime - BeforeNoteTime;

	printConsole("item : %d \n", CRMitemManager::GetInstance()->GetActivatedItem(PLAYER_TWO));

	if ( CRMitemManager::GetInstance()->IsActivedItemForSelf(PLAYER_TWO) == true)
	{
		m_Mental -= 3;
	}
	else
	{
		m_Mental += static_cast<UINT>( CRMitemManager::GetInstance()->GetActivatedItem( PLAYER_TWO ) );
	}

	if ( delayTime > 250 )
	{
		m_Mental -= 3;
	}
	else
	{
		m_Mental += 1;
	}

	if ( m_Mental < 10 )
	{
		m_Mental = 10;
	}
	if ( m_Mental > 90)
	{
		m_Mental = 90;
	}

	UINT temp = CRMrandomGenerator::GetInstance()->GetRandom(0, 1);
	// 2260이 퍼펙범위

	if ( temp == 0)
	{
		m_KeyInputReadyTime = NextNoteTime + CRMrandomGenerator::GetInstance()->GetRandom(m_PerfectTime, m_PerfectTime + m_Mental);
	}
	else
	{
		m_KeyInputReadyTime = NextNoteTime + CRMrandomGenerator::GetInstance()->GetRandom(m_PerfectTime - m_Mental, m_PerfectTime);
	}

	printConsole("Mental : %d %d \n", m_Mental, static_cast<int>(m_KeyInputReadyTime - NextNoteTime));

	m_InputReadyList.push_back(m_KeyInputReadyTime);
	m_InputReadyType.push_back(NextNoteType);

	m_ReadyItem = CRMrandomGenerator::GetInstance()->GetRandom(1, 10);
}

void CRMairTomo::PlayVirtualPlayer()
{

	if ( m_InputReadyList.size() == 0 )
	{
		return;
	}
	
	if ( CRMplayer2P::GetInstance()->IsDead() )
	{
		return;
	}

	std::list<UINT>::iterator iterTime = m_InputReadyList.begin();
	std::list<WidgetType>::iterator iterType = m_InputReadyType.begin();

	if ( CRMsound::GetInstance()->GetPlayTime() > *iterTime)
	{
		//printf_s("COM-%d \n",CRMsound::GetInstance()->GetPlayTime());
		if ( *iterType == WIDGET_NOTE_NORMAL_1 )
		{
			CRMinput::GetInstance()->SetVirtualKeyStatusByKey(KEY_TABLE_P2_TARGET1);
			//printConsole("virtual Player Press left!-%d \n",CRMsound::GetInstance()->GetPlayTime());
			m_InputReadyList.pop_front();
			m_InputReadyType.pop_front();
		}
		else if ( *iterType == WIDGET_NOTE_NORMAL_2 )
		{
			CRMinput::GetInstance()->SetVirtualKeyStatusByKey(KEY_TABLE_P2_TARGET2);
			//printConsole("virtual Player Press right!=-%d \n",CRMsound::GetInstance()->GetPlayTime());
			m_InputReadyList.pop_front();
			m_InputReadyType.pop_front();
		}
	}
}

void CRMairTomo::ItemVirtualPlayer()
{
	// 죽었을때 아이템 사용 막기
	if ( CRMplayer2P::GetInstance()->IsDead() )
	{
		return;
	}

	if ( m_ReadyItem % 10 == 0 )
	{
		CRMinput::GetInstance()->SetVirtualKeyStatusByKey(KEY_TABLE_P2_ATTACK);
	}
}
