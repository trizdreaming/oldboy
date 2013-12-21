#include "stdafx.h"
#include "RMchildJudgeMessage.h"
#include "RMmainLoop.h"
#include "RMjudgeManager.h"


CRMchildJudgeMessage::CRMchildJudgeMessage(void)
{
}


CRMchildJudgeMessage::~CRMchildJudgeMessage(void)
{
}


void CRMchildJudgeMessage::Update()
{
	SetVisibleByScene();

	if ( m_Scene != CRMmainLoop::GetInstance()->GetNowScene() )
	{
		CRMjudgeManager::GetInstance()->InitializeJudgeType();
		m_WidgetType = WIDGET_PLAY_JUDGE_NONE;
		return;
	}

	JudgeType judgeType = CRMjudgeManager::GetInstance()->GetJudgeType( m_PlayerNumber );
	
	switch ( judgeType )
	{
	case JUDGE_PERFECT:
		m_WidgetType = WIDGET_PLAY_JUDGE_PERFECT;
		break;
	case JUDGE_GOOD:
		m_WidgetType = WIDGET_PLAY_JUDGE_GOOD;
		break;
	case JUDGE_MISS:
		m_WidgetType = WIDGET_PLAY_JUDGE_MISS;
		break;
	default:
		m_WidgetType = WIDGET_PLAY_JUDGE_NONE;
		break;
	}
}