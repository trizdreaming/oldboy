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
	m_Phase1Flag(false),
	m_Phase2Flag(false),
	m_Phase3Flag(false),
	m_PositionXOriginal(0.0f),
	m_PositionYOriginal(0.0f),
	m_WidthOriginal(0.0f),
	m_HeightOriginal(0.0f),
	m_FlickCount(0),
	m_FlickFlag(false),
	m_OneTimeFinishFlag(false)
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
		m_Visible = m_Phase1Flag = m_Phase2Flag = m_Phase3Flag = m_OneTimeFinishFlag = false;
		return;
	}

	if ( m_OneTimeFinishFlag == true )
	{
		m_Visible = false;
		return;
	}

	if ( CRMitemManager::GetInstance()->GetActivatedItem(m_PlayerNumber) != ITEM_TYPE_NONE
		&& m_Phase1Flag == false && m_Phase2Flag == false && m_Phase3Flag == false )
	{
		m_WidgetType = CRMitemManager::GetInstance()->GetWidgetTypeOfCard(m_PlayerNumber);
		m_Phase1Flag = true;
		m_OneTimeFinishFlag = false;

		m_PositionX = m_PositionXOriginal;
		m_PositionY = m_PositionYOriginal;

		m_Width = 0.0f;
		m_Height = 0.0f;
		m_Alpha = 0.5f;
		m_FlickFlag = false;
		m_FlickCount = 0;

		return;
	}

	UINT	thisTime = timeGetTime();

	if ( m_Phase1Flag == true )
	{
		if ( m_PrevTime + m_TimeSlice < thisTime )
		{
			m_Alpha += 0.05f;
			m_Width += m_WidthOriginal / 10;
			m_Height += m_HeightOriginal / 10;
			m_PositionX -= m_WidthOriginal / 20;
			m_PositionY -= m_HeightOriginal / 20;

			if ( m_Alpha > 0.98f)
			{
				m_Phase1Flag = false;
				m_Phase2Flag = true;
			}

			m_PrevTime = thisTime;
		}
	}
	if ( m_Phase2Flag == true )
	{
		if ( m_PrevTime + m_TimeSlice < thisTime )
		{
			if ( m_FlickFlag )
			{
				m_Alpha -= 0.05f;

				if ( m_Alpha > 1.0f )
				{
					m_FlickFlag = false;
				}
			}
			else
			{
				m_Alpha += 0.05f;

				if ( m_Alpha < 0.5f )
				{
					m_FlickFlag = true;
				}
			}
			
			if ( m_FlickCount > 10)
			{
				m_Phase2Flag = false;
				m_Phase3Flag = true;
			}

			m_PrevTime = thisTime;
			++m_FlickCount;
		}
	}
	if ( m_Phase3Flag == true )
	{
		if ( m_PrevTime + m_TimeSlice < thisTime )
		{
			m_Alpha -= 0.1f;
			m_Width += m_WidthOriginal / 10;
			m_Height += m_HeightOriginal / 10;
			m_PositionX -= m_WidthOriginal / 20;
			m_PositionY -= m_HeightOriginal / 20;

			if ( m_Alpha < 0.1f )
			{
				m_Phase3Flag = false;
				m_PositionX = m_PositionXOriginal;
				m_PositionY = m_PositionYOriginal;
				m_Width = m_WidthOriginal;
				m_Height = m_HeightOriginal;
				m_OneTimeFinishFlag = true;
				m_Alpha = 1.0f;
				m_Visible = false;
			}

			m_PrevTime = thisTime;
		}
	}
}

void CRMchildItemCardDisplay::SetPosition( float x, float y )
{
	CRMobject::SetPosition(x, y);
	m_PositionXOriginal = m_PositionX;
	m_PositionYOriginal = m_PositionY;
}

void CRMchildItemCardDisplay::Render()
{
	CRMobject::Render();

	if ( m_WidthOriginal == 0 && m_Width != 0)
	{
		m_WidthOriginal = m_Width;
	}
	if ( m_HeightOriginal == 0 && m_Height != 0)
	{
		m_HeightOriginal = m_Height;
	}
}
