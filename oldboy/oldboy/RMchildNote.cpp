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

	if ( m_PositionY >= 0 )
	{
		m_PositionY = static_cast<float>(static_cast<int>(m_PositionY + 5) % 660);
	}
	else
	{
		m_PositionY += 5;
	}
	
	return;
}
