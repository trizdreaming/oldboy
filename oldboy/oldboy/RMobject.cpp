#include "stdafx.h"
#include "RMobject.h"
#include "RMimage.h"
#include "RMresourceManager.h"
#include "RMrender.h"


CRMobject::CRMobject(void):
	m_key(NULL),
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

void CRMobject::render()
{

	if(m_key.c_str() == NULL)
	{
		return;
	}

	CRMimage* thisTexture = CRMresourceManager::GetInstance()->GetTexture(m_key);
	
	//D2D1_RECT_F dxSrc = D2D1::RectF( 0.f, 0.f, m_width, m_height);

	D2D1_RECT_F dxArea = D2D1::RectF( m_xPosition, m_yPosition, m_xPosition+ m_width, m_yPosition+m_height);

	CRMrender::GetInstance()->GetRenderTarget()->DrawBitmap(thisTexture->Get2DImg(),dxArea);
}
