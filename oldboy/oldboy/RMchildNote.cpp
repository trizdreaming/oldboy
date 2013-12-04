#include "stdafx.h"
#include "RMmacro.h"
#include "RMdefine.h"
#include "RMchildNote.h"
#include "RMmainLoop.h"
#include "RMrender.h"
#include "RMresourceManager.h"
#include "RMimage.h"


CRMchildNote::CRMchildNote(void)
{
}


CRMchildNote::~CRMchildNote(void)
{
}

void CRMchildNote::Update()
{
	//SetVisibleByScene();

	if ( m_Scene != CRMmainLoop::GetInstance()->GetNowScene() )
	{
		return;
	}
	
	if ( m_Scene == CRMmainLoop::GetInstance()->GetNowScene() && m_Visible == false )
	{
		m_PositionX = DEFAULT_POSITION_X;
		m_PositionY = DEFAULT_POSITION_Y;

		return;
	}

	if ( m_PositionY < SCREEN_SIZE_Y + NOTE_SIZE )
	{
		m_PositionY += 5;
		m_Rotation++;
	}
	else
	{
		m_Visible = false;
	}
}

void CRMchildNote::Render()
{
	D2D1::Matrix3x2F tempMatrix;
	ZeroMemory(&tempMatrix, sizeof(tempMatrix));

	// 원래 좌표축으로 돌리기 위한 현재 좌표축 임시 저장
	CRMrender::GetInstance()->GetRenderTarget()->GetTransform(&tempMatrix);

	CRMimage* thisTexture = CRMresourceManager::GetInstance()->GetTexture(m_ObjectType);

	if ( thisTexture == nullptr )
	{
		// MessageBox( NULL, ERROR_TEXTURE_NULLPTR, ERROR_TITLE_NULLPTR, MB_OK | MB_ICONSTOP );
		return;
	}
	// 방어 코드 - 텍스쳐에 문제가 발생할 경우 nullptr가 넘어와서, 렌더를 패스하므로 외부에서 처리하지 않아도 됨

	if ( m_Width == 0 )
	{
		m_Width = thisTexture->GetWidth();
	}
	if ( m_Height == 0 )
	{
		m_Height = thisTexture->GetHeight();
	}

	m_Matrix = D2D1::Matrix3x2F::Translation( m_Width / 2, m_Height / 2 ) *
		D2D1::Matrix3x2F::Rotation( m_Rotation, D2D1::Point2F(m_PositionX + (m_Width / 2), m_PositionY + (m_Height / 2)) ) *
		D2D1::Matrix3x2F::Scale( m_ScaleX, m_ScaleY ) *
		D2D1::Matrix3x2F::Translation( -m_Width / 2, -m_Height / 2 );

	//m_Matrix = m_Matrix * m_PrevMatrix;

	CRMrender::GetInstance()->GetRenderTarget()->SetTransform( m_Matrix );

	//부모의 렌더함수를 빌려서 바로 적용하도록 함
	CRMobject::Render();

	//원래의 좌표축으로 돌려 놓는 것
	CRMrender::GetInstance()->GetRenderTarget()->SetTransform( tempMatrix );
}
