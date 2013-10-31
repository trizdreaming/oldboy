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

	return;
}
