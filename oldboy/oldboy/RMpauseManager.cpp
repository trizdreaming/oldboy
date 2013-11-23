#include "stdafx.h"
#include "RMpauseManager.h"
#include "RMchildPauseImage.h"
#include "RMsound.h"
#include "RMnoteManager.h"


CRMpauseManager::CRMpauseManager(void)
{
}


CRMpauseManager::~CRMpauseManager(void)
{
}

void CRMpauseManager::ShowPause()
{
	CRMchildPauseImage::GetInstance()->SetVisible(true);
	CRMsound::GetInstance()->SetPauseBG(true);
	CRMnoteManager::GetInstance()->SetPause(true);
}

void CRMpauseManager::ClosePause()
{
	CRMchildPauseImage::GetInstance()->SetVisible(false);
	CRMsound::GetInstance()->SetPauseBG(false);
	CRMnoteManager::GetInstance()->SetPause(false);
}
