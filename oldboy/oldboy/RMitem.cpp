#include "stdafx.h"
#include "RMmacro.h"
#include "RMitem.h"
#include "RMitemManager.h"


CRMitem::CRMitem(void) :
	m_Tick(0),
	m_ObjectTypeColor(OBJECT_NONE),
	m_TargetPlayer(PLAYER_NONE),
	m_Active(false)
{
}


CRMitem::~CRMitem(void)
{
}

void CRMitem::Update()
{
	if ( ++m_Tick > 30 )
	{
		CRMitemManager::GetInstance()->DeactiveItem( m_OwnPlayer );
		printConsole( "아이템 발동 종료! %d틱 경과 \n", m_Tick );

		m_Active = false;
	}
}
