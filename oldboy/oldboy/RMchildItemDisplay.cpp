#include "stdafx.h"
#include "RMmacro.h"
#include "RMchildItemDisplay.h"
#include "RMitemManager.h"
#include "RMrender.h"

CRMchildItemDisplay::CRMchildItemDisplay(void) :
	m_PrevTime(0),
	m_TimeSlice(5),
	m_RotateFlag(false)
{
}

CRMchildItemDisplay::~CRMchildItemDisplay(void)
{
}

void CRMchildItemDisplay::Update()
{
	SetVisibleByScene();

	m_WidgetType = CRMitemManager::GetInstance()->GetWidgetType(m_ThisTier);
	m_PositionY = CRMitemManager::GetInstance()->GetStackPosition(m_ThisTier);

	if ( m_WidgetType < WIDGET_ITEM_COLOR_MAX && m_WidgetType > WIDGET_ITEM_COLOR_MIN )
	{
		UINT	thisTime = timeGetTime();

		if ( m_PrevTime + m_TimeSlice < thisTime )
		{
			if( m_RotateFlag == true )
			{
				m_Rotation -= 2.f;

				if( m_Rotation <= -8.f )
				{
					m_RotateFlag = false;
				}
			}
			else
			{
				m_Rotation += 2.f;
				
				if ( m_Rotation >= 8.0f )
				{
					m_RotateFlag = true;
				}
			}
			m_PrevTime = thisTime;
		}
	}
	else
	{
		m_Rotation = 0;
	}
	// printConsole("티어 : %d, 오브젝트 타입 : %d, 좌표 : (%f, %f) \n", m_ThisTier, m_WidgetType, m_PositionX, m_PositionY);
}

void CRMchildItemDisplay::Render()
{
	// 원래 좌표축으로 돌리기 위한 현재 좌표축 임시 저장
	CRMrender::GetInstance()->GetRenderTarget()->GetTransform( &m_PrevMatrix );

	if ( m_Width != 0 && m_Height != 0 )
	{
		m_Matrix = D2D1::Matrix3x2F::Rotation( m_Rotation, D2D1::Point2F( m_PositionX + m_Width / 2 , m_PositionY + m_Height / 2 ) );
	}

	CRMrender::GetInstance()->GetRenderTarget()->SetTransform( m_Matrix );

	//부모의 렌더함수를 빌려서 변환 매트릭스 적용하도록 함
	CRMobject::Render();

	//원래의 좌표축으로 돌려 놓는 것
	CRMrender::GetInstance()->GetRenderTarget()->SetTransform( m_PrevMatrix );
}