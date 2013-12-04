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
	m_Rotation = 45.f;
}


CRMchildItemCardDisplay::~CRMchildItemCardDisplay(void)
{
}

void CRMchildItemCardDisplay::Render()
{
	// 원래 좌표축으로 돌리기 위한 현재 좌표축 임시 저장
	CRMrender::GetInstance()->GetRenderTarget()->GetTransform( &m_PrevMatrix );

	// 물체 원래 좌표 값 임시 저장
	float prevPositionX = m_PositionX;
	float prevPositionY = m_PositionY;

	//물체를 좌표 축 (0,0) 위치로 이동 -> 회전 -> 원래 위치로 회복하도록 함
	//매트릭스 초기화
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

	//부모의 렌더함수를 빌려서 변환 매트릭스 적용하도록 함
	CRMobject::Render();

	//원래의 좌표축으로 돌려 놓는 것
	CRMrender::GetInstance()->GetRenderTarget()->SetTransform( m_PrevMatrix );

	//물체가 원래 있던 좌표로 되돌림
	m_PositionX = prevPositionX;
	m_PositionY = prevPositionY;
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
