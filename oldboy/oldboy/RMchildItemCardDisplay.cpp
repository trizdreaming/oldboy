#include "stdafx.h"
#include "RMchildItemCardDisplay.h"
#include "RMmacro.h"
#include "RMitemManager.h"
#include "RMrender.h"


CRMchildItemCardDisplay::CRMchildItemCardDisplay(void):
	m_TimeSlice(10),
	m_PrevTime(0),
	m_FlickFlag(true),
	m_OrderNumber(0),
	m_OrderFlag(false),
	m_MoveOffset(0)
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

	if ( m_Width != 0 && m_Height != 0 )
	{
		m_Matrix = D2D1::Matrix3x2F::Translation( -m_PositionX, -m_PositionY ) * 
			D2D1::Matrix3x2F::Rotation( m_Rotation, D2D1::Point2F( m_Width , m_Height ) ) * 
			D2D1::Matrix3x2F::Translation(m_PositionX + m_MoveOffset, m_PositionY);
	}

	CRMrender::GetInstance()->GetRenderTarget()->SetTransform( m_Matrix );

	//부모의 렌더함수를 빌려서 변환 매트릭스 적용하도록 함
	CRMobject::Render();

	//원래의 좌표축으로 돌려 놓는 것
	CRMrender::GetInstance()->GetRenderTarget()->SetTransform( m_PrevMatrix );
}

void CRMchildItemCardDisplay::Update()
{
	SetVisibleByScene();

	if ( CRMitemManager::GetInstance()->GetActivatedItem(m_PlayerNumber) == ITEM_TYPE_NONE )
	{
		m_Visible = false;
		m_Rotation = 0;
		return;
	}

	UINT	thisTime = timeGetTime();

	if ( m_OrderNumber == 29 )
	{
		if ( m_PrevTime + m_TimeSlice < thisTime )
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
			m_PrevTime = thisTime;
		}
	}
	else
	{
		if ( m_OrderFlag == false )
		{
			if ( m_PrevTime + (m_OrderNumber * 50) < thisTime )
			{
				m_OrderFlag = true;
				m_MoveOffset = 0;
			}
		}
		else
		{
			++m_Rotation;
			++m_MoveOffset;
			m_Alpha -= 0.05f;

			if ( m_Rotation > 20 )
			{
				m_PrevTime = thisTime;
				m_OrderFlag = false;
				m_MoveOffset = 0.f;
				m_Rotation = 0.f;
				m_Alpha = 1.f;
			}
		}
	}
}
