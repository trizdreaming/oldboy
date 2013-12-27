#include "stdafx.h"
#include "RMchildAirTomoFixer.h"
#include "RMdefine.h"
#include "RMairTomo.h"


CRMchildAirTomoFixer::CRMchildAirTomoFixer(void)
{
	m_Alpha = 0.f;
	m_PositionY = NOTE_START_POSITION_Y;
	m_StartTime = timeGetTime();
}


CRMchildAirTomoFixer::~CRMchildAirTomoFixer(void)
{
}

void CRMchildAirTomoFixer::Update()
{
	if ( m_PositionY < NOTE_JUDGE_PERFECT_START_LINE )
	{
		//printConsole("PERFECT Potision:%f\n",m_PositionY);
		m_PositionY += 5;
	}
	else
	{
		UINT elaspedTime = timeGetTime() - m_StartTime;
		CRMairTomo::GetInstance()->SetPerfectTime(elaspedTime);
		//printConsole("PERFECT TIME:%d\n",elaspedTime);

		m_StartTime = timeGetTime();
		m_PositionY = NOTE_START_POSITION_Y;
	}
}
