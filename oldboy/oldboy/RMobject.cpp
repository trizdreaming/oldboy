#include "stdafx.h"
#include "RMmacro.h"
#include "RMobject.h"
#include "RMimage.h"
#include "RMresourceManager.h"
#include "RMrender.h"
#include "RMmainLoop.h"

CRMobject::CRMobject(void):
	m_ObjectType(OBJECT_NONE),
	m_Visible(false),
	m_PositionX(0.0f),
	m_PositionY(0.0f),
	m_Width(0.0f),
	m_Height(0.0f),
	m_Alpha(0.0f)
{
}


CRMobject::~CRMobject(void)
{
}

void CRMobject::Render()
{

	if ( m_ObjectType == OBJECT_NONE || m_Visible == false )
	{
		return;
	}

	CRMimage* thisTexture = CRMresourceManager::GetInstance()->GetTexture(m_ObjectType);

	if ( thisTexture == nullptr )
	{
		return;
	}
	// 방어 코드 - 텍스쳐가 없을 경우

	if ( m_Width == 0 )
	{
		m_Width = thisTexture->GetWidth();
	}
	if ( m_Height == 0 )
	{
		m_Height = thisTexture->GetHeight();
	}

	D2D1_RECT_F dxArea = D2D1::RectF( m_PositionX, m_PositionY, m_PositionX + m_Width, m_PositionY + m_Height);
	
	CRMrender::GetInstance()->GetRenderTarget()->DrawBitmap(thisTexture->Get2DImg(), dxArea);
}

void CRMobject::SetVisibleByScene()
{
	if ( m_Scene == CRMmainLoop::GetInstance()->GetNowScene() )
	{
		m_Visible = true;
	}
	else
	{
		m_Visible = false;
	}
}
