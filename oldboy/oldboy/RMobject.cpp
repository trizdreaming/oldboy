#include "stdafx.h"
#include "RMobject.h"
#include "RMimage.h"
#include "RMresourceManager.h"
#include "RMrender.h"

CRMobject::CRMobject(void):
	m_key(NOTHING),
	m_xPosition(0.0f),
	m_yPosition(0.0f),
	m_width(0.0f),
	m_height(0.0f),
	m_alpha(0.0f)
{
}


CRMobject::~CRMobject(void)
{
}

void CRMobject::Render()
{

	if(m_key == NOTHING)
	{
		return;
	}

	CRMimage* thisTexture = CRMresourceManager::GetInstance()->GetTexture(m_key);

	if(thisTexture == nullptr)
	{
		return;
	}
	// 방어적 프로그래밍 - 텍스쳐가 없을 경우

	if(m_width == 0)
	{
		m_width = thisTexture->GetWidth();
	}
	if(m_height == 0)
	{
		m_height = thisTexture->GetHeight();
	}

	D2D1_RECT_F dxArea = D2D1::RectF( m_xPosition, m_yPosition, m_xPosition + m_width, m_yPosition + m_height);
	
	CRMrender::GetInstance()->GetRenderTarget()->DrawBitmap(thisTexture->Get2DImg(), dxArea);
}
