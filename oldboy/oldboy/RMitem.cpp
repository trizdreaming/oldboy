#include "stdafx.h"
#include "RMmacro.h"
#include "RMitem.h"
#include "RMitemManager.h"


CRMitem::CRMitem(void) :
	m_WidgetTypeForColor(WIDGET_NONE),
	m_WidgetTypeForColorOut(WIDGET_NONE),
	m_TargetPlayer(PLAYER_NONE),
	m_Active(false),
	m_TimeSlice(5000),
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
		printConsole( "%dP 아이템 발동 종료! \n", m_TargetPlayer );
		DeActive();
	}
}

void CRMitem::Active()
{
	m_Active = true;

	m_StartTime = timeGetTime();
}
