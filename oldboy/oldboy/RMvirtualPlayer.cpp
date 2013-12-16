#include "stdafx.h"
#include "RMvirtualPlayer.h"
#include "RMrandomGenerator.h"
#include "RMinput.h"
#include "RMsound.h"
#include "RMmacro.h"


CRMvirtualPlayer::CRMvirtualPlayer(void)
{
	Initialize();
}


CRMvirtualPlayer::~CRMvirtualPlayer(void)
{
}

void CRMvirtualPlayer::Initialize()
{
	m_Mental = 15;
	m_KeyInputReadyTime = 0;
	m_KeyInputReadyType = WIDGET_NOTE_NORMAL_1;

	m_InputReadyList.clear();
	m_InputReadyType.clear();

	m_ReadyItem = 0;
}

void CRMvirtualPlayer::SetRandomJudge( UINT NextNoteTime, WidgetType NextNoteType , UINT BeforeNoteTime )
{
	
	m_KeyInputReadyType = NextNoteType;
	//printConsole("virtual Player CALL SetRandomJudge! %d\n",NextNoteTime);
	int delayTime = NextNoteTime - BeforeNoteTime;

	// ¸àÅ»ÀÌ ÄÄÅÍÀÇ ¿À·ù È®·üÀ» Á¶Á¤ÇÔ
	// ¾ÆÀÌÅÛ °ø°ÝÀ» ¹Þ¾ÒÀ»¶§³ª ¸àÅ»ºØ±«
	// ´À¸°³ëÆ®°¡ ³ª¿À¸é ¸àÅ»È¸º¹

	if ( delayTime > 2000 )
	{
		m_Mental -= 1;
	}
	else
	{
		m_Mental += 1;
	}

	if ( m_Mental < 1 )
	{
		m_Mental = 1;
	}

	// 2260ÀÌ ÆÛÆå¹üÀ§
	m_KeyInputReadyTime = NextNoteTime + CRMrandomGenerator::GetInstance()->GetRandom(2260,2275);

	m_InputReadyList.push_back(m_KeyInputReadyTime);
	m_InputReadyType.push_back(NextNoteType);



	m_ReadyItem = CRMrandomGenerator::GetInstance()->GetRandom(1, 10);
	

}

void CRMvirtualPlayer::PlayVirtualPlayer()
{
	if ( m_InputReadyList.size() == 0 )
	{
		return;
	}
	
	std::list<UINT>::iterator iterTime = m_InputReadyList.begin();
	std::list<WidgetType>::iterator iterType = m_InputReadyType.begin();

	if ( CRMsound::GetInstance()->GetPlayTime() > *iterTime)
	{
		
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

void CRMvirtualPlayer::ItemVirtualPlayer()
{
	if ( m_ReadyItem % 10 == 0 )
	{
		CRMinput::GetInstance()->SetVirtualKeyStatusByKey(KEY_TABLE_P2_ATTACK);
	}
}
