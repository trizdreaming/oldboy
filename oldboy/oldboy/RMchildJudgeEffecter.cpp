#include "stdafx.h"
#include "RMchildJudgeEffecter.h"
#include "RMmainLoop.h"
#include "RMglobalParameterManager.h"
#include "RMrender.h"


CRMchildJudgeEffecter::CRMchildJudgeEffecter(void):
	m_AnimationFrame(0)
{
}


CRMchildJudgeEffecter::~CRMchildJudgeEffecter(void)
{
}

void CRMchildJudgeEffecter::Update()
{
	if ( m_Scene != CRMmainLoop::GetInstance()->GetNowScene() )
	{
		m_Visible = false;
		return;
	}
	m_Visible = true;

	//////////////////////////////////////////////////////////////////////////

	JudgeType NowJudgeType = JUDGE_NONE;

	if (m_PlayerNumber == PLAYER_ONE)
	{
		NowJudgeType = CRMglobalParameterManager::GetInstance()->GetP1JudgeType();
	}
	else
	{
		NowJudgeType = CRMglobalParameterManager::GetInstance()->GetP2JudgeType();
	}

	CRMglobalParameterManager::GetInstance()->SetPlayerJudgeType(m_PlayerNumber, JUDGE_NONE);

	m_Rotation += 15.0f;
	if ( m_Rotation > 360.0f )
	{
		m_Rotation -= 360.0f;
	}

	switch ( NowJudgeType )
	{
	case JUDGE_PERFECT:
		m_WidgetType = WIDGET_PLAY_JUDGE_EFFECT_PERFECT;
		m_AnimationFrame = 0;
		break;
	case JUDGE_GOOD:
		m_WidgetType = WIDGET_PLAY_JUDGE_EFFECT_GOOD;
		m_AnimationFrame = 0;
		break;
	case JUDGE_MISS:
		m_WidgetType = WIDGET_PLAY_JUDGE_EFFECT_MISS;
		m_AnimationFrame = 0;
		break;
	default:
		if ( m_AnimationFrame > 8 )
		{
			m_WidgetType = WIDGET_PLAY_JUDGE_EFFECT_NONE;
			m_AnimationFrame = 0;
		}
		break;
	}

	++m_AnimationFrame;

}

void CRMchildJudgeEffecter::Render()
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