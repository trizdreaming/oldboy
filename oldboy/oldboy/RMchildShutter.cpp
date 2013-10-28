#include "stdafx.h"
#include "RMchildShutter.h"


CRMchildShutter::CRMchildShutter(void) :
	m_Tick(0)
{
}


CRMchildShutter::~CRMchildShutter(void)
{
}

void CRMchildShutter::Update()
{
	CRMobject::Update();

	++m_Tick;

	if(m_Tick >= 780)
	{
		m_PositionY = static_cast<float>(static_cast<int>(m_PositionY + 110));

		if(m_PositionY > 10)
			m_PositionY = -660;

		m_Tick = 600;
	}

	return;
}
