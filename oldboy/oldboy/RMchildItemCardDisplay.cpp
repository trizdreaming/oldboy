#include "stdafx.h"
#include "RMchildItemCardDisplay.h"
#include "RMmacro.h"
#include "RMitemManager.h"
#include "RMrender.h"
#include "RMplayer1P.h"
#include "RMplayer2P.h"



CRMchildItemCardDisplay::CRMchildItemCardDisplay(void):
	m_TimeSlice(30),
	m_PrevTime(0),
	m_FlickFlag(true),
	m_PositionXOriginal(0.0f),
	m_PositionYOriginal(0.0f),
	m_WidthOriginal(0.0f)
{
}


CRMchildItemCardDisplay::~CRMchildItemCardDisplay(void)
{
}

void CRMchildItemCardDisplay::Update()
{
	SetVisibleByScene();

	if ( m_Visible == false )
	{
		return;
	}
	if ( (m_PlayerNumber == PLAYER_ONE && CRMplayer1P::GetInstance()->IsDead()) || 
		(m_PlayerNumber == PLAYER_TWO && CRMplayer2P::GetInstance()->IsDead()) )
	{
		m_Visible = false;
		return;
	}

	if ( CRMitemManager::GetInstance()->GetActivatedItem(m_PlayerNumber) == ITEM_TYPE_NONE )
	{
		m_Visible = false;
		 //m_Rotation = 0;

		return;
	}

	m_WidgetType = CRMitemManager::GetInstance()->GetWidgetTypeOfCard(m_PlayerNumber);

	UINT	thisTime = timeGetTime();

	if( m_PrevTime + m_TimeSlice < thisTime )
	{
		if( m_FlickFlag == true )
		{
			m_Alpha -= 0.1f;
			if( m_Alpha <= 0.0f )
			{
				m_FlickFlag = false;
			}
		}
		else
		{
			m_Alpha += 0.2f;
			if ( m_Alpha >= 1.0f )
			{
				m_FlickFlag = true;
			}
		}
		//printConsole("알파 값: %f \n", m_Alpha);
		m_PrevTime = thisTime;

	}
}

void CRMchildItemCardDisplay::SetPosition( float x, float y )
{
	CRMobject::SetPosition(x, y);
	m_PositionXOriginal = x;
	m_PositionYOriginal = y;
}
