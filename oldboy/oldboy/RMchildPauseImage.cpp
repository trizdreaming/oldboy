#include "stdafx.h"
#include "RMchildPauseImage.h"
#include "RMpauseManager.h"
#include "RMobject.h"
#include "RMmainLoop.h"


CRMchildPauseImage::CRMchildPauseImage(void):
	m_ObjectType1(OBJECT_PAUSE_IMAGE_PLAY_OK)
{
}


CRMchildPauseImage::~CRMchildPauseImage(void)
{
}

void CRMchildPauseImage::Update()
{
	m_Visible = CRMpauseManager::GetInstance()->IsPause();

	if ( m_Visible )
	{
		//SM9: 이런건 if 두번으로 중첩해라..
		if ( CRMmainLoop::GetInstance()->GetNowScene() == SCENE_PLAY && CRMpauseManager::GetInstance()->IsPauseSelectedCancel() )
		{
			m_ObjectType = OBJECT_PAUSE_IMAGE_PLAY_CANCEL;
		}
		else if ( CRMmainLoop::GetInstance()->GetNowScene() == SCENE_PLAY && !CRMpauseManager::GetInstance()->IsPauseSelectedCancel() )
		{
			m_ObjectType = OBJECT_PAUSE_IMAGE_PLAY_OK;
		}

		else if ( CRMmainLoop::GetInstance()->GetNowScene() == SCENE_TITLE && CRMpauseManager::GetInstance()->IsPauseSelectedCancel() )
		{
			m_ObjectType = OBJECT_PAUSE_IMAGE_TITLE_CANCEL;
		}
		else if ( CRMmainLoop::GetInstance()->GetNowScene() == SCENE_TITLE && !CRMpauseManager::GetInstance()->IsPauseSelectedCancel() )
		{
			m_ObjectType = OBJECT_PAUSE_IMAGE_TITLE_OK;
		}
	}

	
}
