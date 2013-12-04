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
	// 원래 좌표축으로 돌리기 위한 현재 좌표축 임시 저장
	CRMrender::GetInstance()->GetRenderTarget()->GetTransform( &m_PrevMatrix );

	float prevPositionX = m_PositionX;
	float prevPositionY = m_PositionY;

	D2D1::IdentityMatrix();

	if ( m_Width != 0 && m_Height != 0 )
	{
		m_Matrix = D2D1::Matrix3x2F::Rotation( m_Rotation, D2D1::Point2F( m_Width / 2 , m_Height / 2 ) ) * 
			D2D1::Matrix3x2F::Translation(m_PositionX, m_PositionY);
	}

	if ( m_Width != 0 && m_Height != 0 )
	{
		m_PositionX = 0.f;
		m_PositionY = 0.f;
	}

	CRMrender::GetInstance()->GetRenderTarget()->SetTransform( m_Matrix );

	//부모의 렌더함수를 빌려서 바로 적용하도록 함
	
	CRMobject::Render();

	//원래의 좌표축으로 돌려 놓는 것
	CRMrender::GetInstance()->GetRenderTarget()->SetTransform( m_PrevMatrix );

	m_PositionX = prevPositionX;
	m_PositionY = prevPositionY;
}
