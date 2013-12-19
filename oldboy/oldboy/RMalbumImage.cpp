#include "stdafx.h"
#include "RMmacro.h"
#include "RMdefine.h"
#include "RMalbumImage.h"
#include "RMrender.h"


CRMalbumImage::CRMalbumImage(void) :
	m_IsUp(false), m_IsDown(false), m_IsFinish(true)
{
}


CRMalbumImage::~CRMalbumImage(void)
{
}


void CRMalbumImage::Update()
{
	if ( m_IsUp == false && m_IsDown == false )
	{
		m_PositionX = 0;
		m_PositionY = DEFAULT_POSITION_Y;
		m_Visible = false;
		m_IsFinish = true;

		return;
	}

	m_Visible = true;

	if ( m_IsUp )
	{
		m_PositionY -= 40;
		if ( m_PositionY < 1 )
		{
			m_IsUp = false;
			m_IsFinish = true;
		}
	}
	if ( m_IsDown )
	{
		m_PositionY += 40;
		if ( m_PositionY > -1 )
		{
			m_IsDown = false;
			m_IsFinish = true;
		}
	}
}

void CRMalbumImage::Up()
{
	m_IsUp = true;
	m_IsFinish = false;
	m_PositionY = SCREEN_SIZE_Y + 18;
}

void CRMalbumImage::Down()
{
	m_IsDown = true;
	m_IsFinish = false;
	m_PositionY = -SCREEN_SIZE_Y - 18;
}
