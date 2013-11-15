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
	
	if ( m_PositionY < SCREEN_SIZE_Y + NOTE_SIZE )
	{
		m_PositionY += 5;
	}
	else
	{
		m_Visible = false;
	}

	return;
}
