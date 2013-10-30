#include "stdafx.h"
#include "oldboy.h"
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
	CRMobject::SetVisibleByScene();

	if ( m_Scene != CRMmainLoop::GetInstance()->GetNowScene() )
	{
		return;
	}

	m_PositionY += 5;

	if (m_PositionY > SCREEN_SIZE_Y)
	{
		m_PositionY = -150;
	}
	
	return;
}
