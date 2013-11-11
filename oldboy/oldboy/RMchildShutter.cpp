#include "stdafx.h"
#include "oldboy.h"
#include "RMchildShutter.h"
#include "RMmainLoop.h"
#include "RMplayer1P.h"
#include "RMplayer2P.h"


CRMchildShutter::CRMchildShutter(void) :
	m_Tick(0)
{
}


CRMchildShutter::~CRMchildShutter(void)
{
}

void CRMchildShutter::Update()
{
	// SetVisibleByScene();

	if ( m_Scene != CRMmainLoop::GetInstance()->GetNowScene() )
	{
		return;
	}

	m_Visible = true;

	if ( m_PositionY < -10 )
	{
		switch (m_playerNumber)
		{
		case PLAYER_ONE:
			m_PositionX = SHUTTER_P1_START_POSITION_X;
			m_PositionY = SHUTTER_START_POSITION_Y + (PLAYER_HP_MAX - (float) CRMplayer1P::GetInstance()->GetHP() ) * -((float) SHUTTER_START_POSITION_Y / 10);
			break;
		case PLAYER_TWO:
			m_PositionX = SHUTTER_P2_START_POSITION_X;
			m_PositionY = SHUTTER_START_POSITION_Y + (PLAYER_HP_MAX - (float) CRMplayer2P::GetInstance()->GetHP() ) * -((float) SHUTTER_START_POSITION_Y / 10);
			break;
		default:
			break;
		}
	}

	return;
}
