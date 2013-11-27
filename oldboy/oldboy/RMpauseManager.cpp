#include "stdafx.h"
#include "RMpauseManager.h"
#include "RMsound.h"
#include "RMnoteManager.h"
#include "RMmainLoop.h"


CRMpauseManager::CRMpauseManager(void):
	m_IsPause(false),
	m_PauseSelectCancel(true)
{
}


CRMpauseManager::~CRMpauseManager(void)
{
}

void CRMpauseManager::ShowPause()
{
	if ( CRMmainLoop::GetInstance()->GetNowScene() != SCENE_SELECT_MUSIC )
	{
		m_IsPause = true;
		if ( CRMmainLoop::GetInstance()->GetNowScene() == SCENE_PLAY )
		{
			CRMsound::GetInstance()->SetPauseBG(true);
		}

		CRMnoteManager::GetInstance()->StartPause();
	}

}

void CRMpauseManager::ClosePause()
{
	m_IsPause = false;
	if ( CRMmainLoop::GetInstance()->GetNowScene() == SCENE_PLAY )
	{
		CRMsound::GetInstance()->SetPauseBG(false);
	}
	
	CRMnoteManager::GetInstance()->EndPause();
}
