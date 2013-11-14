#include "stdafx.h"
#include "oldboy.h"
#include "RMchildShutter.h"
#include "RMmainLoop.h"
#include "RMplayer1P.h"
#include "RMplayer2P.h"


CRMchildShutter::CRMchildShutter(void) :
	m_Tick(0),
	m_playerNumber(PLAYER_NONE)
{
}


CRMchildShutter::~CRMchildShutter(void)
{
}

void CRMchildShutter::Update()
{
	float resultPosition = 0.0f;
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
			resultPosition = SHUTTER_START_POSITION_Y + (PLAYER_HP_MAX - (float) CRMplayer1P::GetInstance()->GetHP() ) * -((float) SHUTTER_START_POSITION_Y / 10);
			if ( (int)m_PositionY != (int)resultPosition )
			{
				m_PositionY += (resultPosition-m_PositionY) / 20;
			}
			break;
		case PLAYER_TWO:
			m_PositionX = SHUTTER_P2_START_POSITION_X;
			resultPosition = SHUTTER_START_POSITION_Y + (PLAYER_HP_MAX - (float) CRMplayer2P::GetInstance()->GetHP() ) * -((float) SHUTTER_START_POSITION_Y / 10);
			if ( (int)m_PositionY != (int)resultPosition )
			{
				m_PositionY += (resultPosition-m_PositionY) / 20;
			}
			break;
		default:
			break;
		}
	}

	return;
}
