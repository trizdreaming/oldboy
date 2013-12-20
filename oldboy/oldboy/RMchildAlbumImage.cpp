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
		m_PositionX = DEFAULT_POSITION_X;
		m_PositionY = DEFAULT_POSITION_Y;
		m_Visible = false;
		m_IsFinish = true;
		m_Width = SCREEN_SIZE_X;
		m_Height = SCREEN_SIZE_Y;

		return;
	}

	m_Visible = true;

	if ( m_IsUp )
	{
		m_PositionX += 40;
		m_PositionY -= 40;
		m_Width -= 40;
		m_Height -= 20;
		if ( m_PositionY < 1 )
		{
			m_IsUp = false;
			m_IsFinish = true;
		}
	}
	if ( m_IsDown )
	{
		m_PositionX -= 40;
		m_PositionY += 40;
		m_Width += 40;
		m_Height += 20;
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
	m_PositionX = -680;
	m_PositionY = SCREEN_SIZE_Y + 18;
	m_Width = SCREEN_SIZE_X + 680;
	m_Height = SCREEN_SIZE_Y + 340;
}

void CRMchildAlbumImage::Down()
{
	m_IsDown = true;
	m_IsFinish = false;
	m_PositionX = 680;
	m_PositionY = -SCREEN_SIZE_Y - 18;
	m_Width = SCREEN_SIZE_X - 680;
	m_Height = SCREEN_SIZE_Y - 340;
}
