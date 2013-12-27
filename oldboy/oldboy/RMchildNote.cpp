#include "stdafx.h"
#include "RMmacro.h"
#include "RMdefine.h"
#include "RMchildNote.h"
#include "RMmainLoop.h"
#include "RMrender.h"
#include "RMresourceManager.h"
#include "RMimage.h"
#include "RMitemManager.h"


CRMchildNote::CRMchildNote(void) :
	m_StartTime(0),
	m_Original_type(WIDGET_NONE)
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
		m_Rotation = 0.f;
		m_Alpha = 1.f;

		return;
	}

	if ( m_PositionY < SCREEN_SIZE_Y + NOTE_SIZE )
	{
		UINT thisTime = timeGetTime();
		int elapsedTime = thisTime - m_StartTime;

		m_PositionY = static_cast<float>
			( NOTE_START_POSITION_Y + ( static_cast<float>(elapsedTime) / 16) * ( (-NOTE_START_POSITION_Y + SCREEN_SIZE_Y + NOTE_SIZE) / 140) );
		
		printConsole ("E : %d  A : %f  Y : %f \n", elapsedTime, m_Alpha, m_PositionY);

		if ( CRMitemManager::GetInstance()->GetActivatedItem(m_PlayerNumber) == ITEM_T2_ROTATE )
		{
			if ( m_PositionY > NOTE_JUDGE_PERFECT_START_LINE - 540 )
			{
				m_Rotation = 180 + ( m_PositionY - ( NOTE_JUDGE_PERFECT_START_LINE - 540 ) ) / 3;
			}
		}
		else if ( CRMitemManager::GetInstance()->GetActivatedItem(m_PlayerNumber) == ITEM_T3_REVERSE )
		{
			if ( m_PositionY + 80 < NOTE_JUDGE_PERFECT_START_LINE && 
				( ( static_cast<int>(m_PositionY) + 80 ) / ( NOTE_JUDGE_PERFECT_START_LINE / 6 ) ) % 2 == 1 )
			{
				if ( m_Original_type == WIDGET_NOTE_NORMAL_1 )
				{
					m_WidgetType = WIDGET_NOTE_NORMAL_2;
				}
				else
				{
					m_WidgetType = WIDGET_NOTE_NORMAL_1;
				}
			}
			else
			{
				m_WidgetType = m_Original_type;
			}
		}
		else if (CRMitemManager::GetInstance()->GetActivatedItem(m_PlayerNumber) == ITEM_T1_MIST  )
		{
			int tempPositionY = static_cast<int>(m_PositionY);

			if ( tempPositionY >= 0 && tempPositionY <= 150 )
			{
				if ( (tempPositionY % 15) == 0 )
				{
					m_Alpha -= 0.1f;
				}
			}
			else if ( tempPositionY >= 150 && tempPositionY <= 380 )
			{
				m_Alpha = 0.0;
			}
			else
			{
				if ( m_Alpha < 1.0f && (tempPositionY % 15) == 0 )
				{
					m_Alpha += 0.1f;
				}
				if ( m_Alpha > 1.0 )
				{
					m_Alpha = 1.0f;
				}
			}
		}
		else
		{
			m_WidgetType = m_Original_type;
			m_Rotation = 0.0f;
			m_Alpha = 1.0f;
		}
		
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

	if ( m_Width != 0 && m_Height != 0 )
	{
		m_Matrix = D2D1::Matrix3x2F::Rotation( m_Rotation, D2D1::Point2F( m_PositionX + (m_Width / 2) , m_PositionY + (m_Height / 2) ) );
	}

	CRMrender::GetInstance()->GetRenderTarget()->SetTransform( m_Matrix );

	//부모의 렌더함수를 빌려서 바로 적용하도록 함	
	CRMobject::Render();

	//원래의 좌표축으로 돌려 놓는 것
	CRMrender::GetInstance()->GetRenderTarget()->SetTransform( m_PrevMatrix );
}

void CRMchildNote::SetWidgetType( WidgetType widgetType )
{
	m_Original_type = widgetType;
	CRMobject::SetWidgetType(widgetType);
}

void CRMchildNote::StartMove()
{
	m_StartTime = timeGetTime();
}
