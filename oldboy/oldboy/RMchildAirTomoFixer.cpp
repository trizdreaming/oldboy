#include "stdafx.h"
#include "RMchildAirTomoFixer.h"
#include "RMdefine.h"
#include "RMairTomo.h"
#include "RMmainLoop.h"
#include "RMsound.h"

CRMchildAirTomoFixer::CRMchildAirTomoFixer(void)
{
	m_Alpha = 0.0f;
	m_PositionY = NOTE_START_POSITION_Y;
}


CRMchildAirTomoFixer::~CRMchildAirTomoFixer(void)
{
}

void CRMchildAirTomoFixer::StartFixer()
{
	m_PositionY = NOTE_START_POSITION_Y;
	m_StartTime = CRMsound::GetInstance()->GetPlayTime();
}

void CRMchildAirTomoFixer::Update()
{
	if ( m_Scene != CRMmainLoop::GetInstance()->GetNowScene() && 
		CRMmainLoop::GetInstance()->GetNowScene() != SCENE_TUTORIAL )
	{
		return;
	}

	if ( CRMairTomo::GetInstance()->IsStart() )
	{
		m_PositionY = NOTE_START_POSITION_Y;
		m_StartTime = CRMsound::GetInstance()->GetPlayTime();
	}

	if ( m_PositionY < NOTE_JUDGE_PERFECT_START_LINE)
	{
		//printConsole("PERFECT Potision:%f\n",m_PositionY);
		m_PositionY += 5;
	}
	else
	{
		UINT elaspedTime = CRMsound::GetInstance()->GetPlayTime() - m_StartTime;
		CRMairTomo::GetInstance()->SetPerfectTime(elaspedTime);
		//printf_s("PERFECT TIME:%d\n",elaspedTime);

		m_StartTime = CRMsound::GetInstance()->GetPlayTime();
		m_PositionY = NOTE_START_POSITION_Y;
	}
}
