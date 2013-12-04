#include "stdafx.h"
#include "RMchildItemCardDisplay.h"
#include "RMmacro.h"
#include "RMitemManager.h"
#include "RMrender.h"


CRMchildItemCardDisplay::CRMchildItemCardDisplay(void):
	m_TimeSlice(10),
	m_PrevTime(0),
	m_FlickFlag(true)
{
	ZeroMemory(&m_Matrix, sizeof(m_Matrix));
	ZeroMemory(&m_PrevMatrix, sizeof(m_PrevMatrix));
}


CRMchildItemCardDisplay::~CRMchildItemCardDisplay(void)
{
}

void CRMchildItemCardDisplay::Render()
{
	// 원래 좌표축으로 돌리기 위한 현재 좌표축 임시 저장
	CRMrender::GetInstance()->GetRenderTarget()->GetTransform( &m_PrevMatrix );
	
	m_Matrix = D2D1::Matrix3x2F::Translation( -100.f/2.f, -175.f/2.f ) *
		D2D1::Matrix3x2F::Rotation( 45.0f , D2D1::Point2F(m_PositionX, m_PositionY)) *
		D2D1::Matrix3x2F::Scale( m_ScaleX, m_ScaleY ) *
		D2D1::Matrix3x2F::Translation( 100.f/2.f, 175.f/2.f );

	CRMrender::GetInstance()->GetRenderTarget()->SetTransform( m_Matrix );

	//부모의 렌더함수를 빌려서 바로 적용하도록 함
	CRMobject::Render();

	//원래의 좌표축으로 돌려 놓는 것
	CRMrender::GetInstance()->GetRenderTarget()->SetTransform( m_PrevMatrix );
}

void CRMchildItemCardDisplay::Update()
{
	SetVisibleByScene();

	UINT	thisTime = timeGetTime();

	if( m_PrevTime + m_TimeSlice < thisTime )
	{
		if( m_FlickFlag == true )
		{
			m_Alpha -= 0.02f;

			if( m_Alpha <= 0.3f )
			{
				m_FlickFlag = false;
			}
		}
		else
		{
			m_Alpha += 0.1f;

			if ( m_Alpha >= 1.0f )
			{
				m_FlickFlag = true;
			}
		}



		//printConsole("알파 값: %f \n", m_Alpha);
		
		m_PrevTime = thisTime;

	}
	

	//아이템이 발동되면 해당 카드가 떠 있도록 함
	if ( CRMitemManager::GetInstance()->GetActivatedItem(m_PlayerNumber) == ITEM_TYPE_NONE )
	{
		m_Visible = false;
	}

}
