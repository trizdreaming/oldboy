#include "stdafx.h"
#include "RMmacro.h"
#include "RMdefine.h"
#include "RMchildShutter.h"
#include "RMmainLoop.h"
#include "RMplayer1P.h"
#include "RMplayer2P.h"


CRMchildShutter::CRMchildShutter(void)
{
}


CRMchildShutter::~CRMchildShutter(void)
{
}

void CRMchildShutter::Update()
{
	SetVisibleByScene();

	float resultPosition = 0.0f;
	
	if ( m_Scene != CRMmainLoop::GetInstance()->GetNowScene() )
	{
		if ( m_PositionY != SHUTTER_START_POSITION_Y )
		{
			printConsole( "셔터 초기화 \n" );
			m_PositionY = SHUTTER_START_POSITION_Y;
		}
		return;
	}

	m_Visible = true;

	if ( (m_PlayerNumber == PLAYER_ONE && CRMplayer1P::GetInstance()->IsEnd()) ||
			(m_PlayerNumber == PLAYER_TWO && CRMplayer2P::GetInstance()->IsEnd()) )
	{
		m_PositionY = 0;
		return;
	}

	if ( m_PlayerNumber == PLAYER_ONE )
	{
		m_PositionX = SHUTTER_P1_START_POSITION_X;
	}
	else
	{
		m_PositionX = SHUTTER_P2_START_POSITION_X;
	}

	if ( m_PositionY >= -1 )
	{
		if ( m_PlayerNumber == PLAYER_ONE )
		{
			CRMplayer1P::GetInstance()->End();
		}
		if ( m_PlayerNumber == PLAYER_TWO )
		{
			CRMplayer2P::GetInstance()->End();
		}
	}

	if ( m_PositionY > SHUTTER_DEAD_LINE + SHUTTER_START_POSITION_Y )
	{
		resultPosition = 0;
	}
	else if ( m_PlayerNumber == PLAYER_ONE)
	{
		resultPosition = SHUTTER_START_POSITION_Y + (PLAYER_HP_MAX - (float) CRMplayer1P::GetInstance()->GetHP() ) * -((float) SHUTTER_START_POSITION_Y / PLAYER_HP_MAX);
	}
	else
	{
		resultPosition = SHUTTER_START_POSITION_Y + (PLAYER_HP_MAX - (float) CRMplayer2P::GetInstance()->GetHP() ) * -((float) SHUTTER_START_POSITION_Y / PLAYER_HP_MAX);
	}

	if ( (int)m_PositionY != (int)resultPosition )
	{
		m_PositionY += ( (resultPosition - m_PositionY) / 20 );
	}
}
