#include "stdafx.h"
#include "RMmacro.h"
#include "RMdefine.h"
#include "RMchildNote.h"
#include "RMmainLoop.h"


CRMchildNote::CRMchildNote(void)
{
}


CRMchildNote::~CRMchildNote(void)
{
}

void CRMchildNote::Update()
{
	// SetVisibleByScene();

	if ( m_Scene != CRMmainLoop::GetInstance()->GetNowScene() )
	{
		return;
	}
	
	if ( m_Scene == CRMmainLoop::GetInstance()->GetNowScene() && m_Visible == false )
	{
		m_PositionX = DEFAULT_POSITION_X;
		m_PositionY = DEFAULT_POSITION_Y;

		return;
	}

	if ( m_PositionY < SCREEN_SIZE_Y + NOTE_SIZE )
	{
		m_PositionY += 5;
	}
	else
	{
		m_Visible = false;
	}
}
