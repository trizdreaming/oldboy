#include "stdafx.h"
#include "RMmacro.h"
#include "RMdefine.h"
#include "RMchildAlbumImage.h"
#include "RMrender.h"


CRMchildAlbumImage::CRMchildAlbumImage(void) :
	m_IsUp(false), m_IsDown(false), m_IsFinish(true)
{
}


CRMchildAlbumImage::~CRMchildAlbumImage(void)
{
}


void CRMchildAlbumImage::Update()
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

void CRMchildAlbumImage::Up()
{
	m_IsUp = true;
	m_IsFinish = false;
	m_PositionY = SCREEN_SIZE_Y + 18;
}

void CRMchildAlbumImage::Down()
{
	m_IsDown = true;
	m_IsFinish = false;
	m_PositionY = -SCREEN_SIZE_Y - 18;
}
