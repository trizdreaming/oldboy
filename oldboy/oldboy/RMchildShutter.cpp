#include "stdafx.h"
#include "oldboy.h"
#include "RMchildShutter.h"
#include "RMmainLoop.h"


CRMchildShutter::CRMchildShutter(void) :
	m_Tick(0)
{
}


CRMchildShutter::~CRMchildShutter(void)
{
}

void CRMchildShutter::Update()
{
	CRMobject::SetVisibleByScene();

	if ( m_Scene != CRMmainLoop::GetInstance()->GetNowScene() )
	{
		return;
	}

	++m_Tick;

	if ( m_Tick >= 780 )
	{
		m_PositionY = static_cast<float>(static_cast<int>(m_PositionY + 112));

		if ( m_PositionY > 10 )
			m_PositionY = -670;

		m_Tick = 600;
	}

	return;
}
