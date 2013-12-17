#include "stdafx.h"
#include "RMchildUIResultImage.h"
#include "RMplayer.h"
#include "RMplayer1P.h"
#include "RMplayer2P.h"


CRMchildUIResultImage::CRMchildUIResultImage(void)
{
}


CRMchildUIResultImage::~CRMchildUIResultImage(void)
{
}

void CRMchildUIResultImage::Update()
{
	SetVisibleByScene();

	CRMplayer*	playerMe;
	CRMplayer*	playerEnemy;
	if ( m_PlayerNumber == PLAYER_ONE )
	{
		playerMe = CRMplayer1P::GetInstance();
		playerEnemy = CRMplayer2P::GetInstance();
	}
	else
	{
		playerMe = CRMplayer2P::GetInstance();
		playerEnemy = CRMplayer1P::GetInstance();
	}

	UINT myTotalScore = playerMe->GetCount(COUNT_SCORE) + ( playerMe->GetCount(COUNT_MAX_COMBO) * SCORE_MAX_COMBO_RATE );
	UINT enemyTotalScore = playerEnemy->GetCount(COUNT_SCORE) + ( playerEnemy->GetCount(COUNT_MAX_COMBO) * SCORE_MAX_COMBO_RATE );

	if ( myTotalScore > enemyTotalScore )
	{
		if ( playerMe->IsDead() )
		{
			m_WidgetType = WIDGET_UI_IMAGE_RESULT_WIN_FAIL;
		}
		else
		{
			m_WidgetType = WIDGET_UI_IMAGE_RESULT_WIN_CLEAR;
		}
	}
	else
	{
		if ( playerMe->IsDead() )
		{
			m_WidgetType = WIDGET_UI_IMAGE_RESULT_LOSE_FAIL;
		}
		else
		{
			m_WidgetType = WIDGET_UI_IMAGE_RESULT_LOSE_CLEAR;
		}
	}
}

