#include "stdafx.h"
#include "RMmacro.h"
#include "RMitem.h"
#include "RMitemManager.h"


CRMitem::CRMitem(void) :
	m_TimeSlice(0),
	m_ObjectTypeColor(OBJECT_NONE),
	m_TargetPlayer(PLAYER_NONE),
	m_Active(false),
	m_StartTime(0)
{
}


CRMitem::~CRMitem(void)
{
}

void CRMitem::Update()
{
	if ( m_Active == false )
	{
		return;
	}

	if ( m_StartTime + m_TimeSlice < timeGetTime() )
	{
		CRMitemManager::GetInstance()->DeactiveItem( m_TargetPlayer );
		printConsole( "%dP 아이템 발동 종료! %d틱 경과 \n", m_TargetPlayer, m_Tick );

		m_Active = false;
	}
}

void CRMitem::Active()
{
	m_Active = true;

	m_StartTime = timeGetTime();
}
