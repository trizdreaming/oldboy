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

	CRMplayer*	player1 = CRMplayer1P::GetInstance();
	CRMplayer*	player2 = CRMplayer2P::GetInstance();

	UINT totalScoreP1 = player1->GetCount(COUNT_SCORE) + ( player1->GetCount(COUNT_MAX_COMBO) * SCORE_MAX_COMBO_RATE );
	UINT totalScoreP2 = player2->GetCount(COUNT_SCORE) + ( player2->GetCount(COUNT_MAX_COMBO) * SCORE_MAX_COMBO_RATE );

	if ( m_PlayerNumber == PLAYER_ONE )
	{
		if ( totalScoreP1 > totalScoreP2 )
		{
			if ( player1->IsDead() )
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
			if ( player1->IsDead() )
			{
				m_WidgetType = WIDGET_UI_IMAGE_RESULT_LOSE_FAIL;
			}
			else
			{
				m_WidgetType = WIDGET_UI_IMAGE_RESULT_LOSE_CLEAR;
			}
		}
	}
	else
	{
		if ( totalScoreP1 < totalScoreP2 )
		{
			if ( player2->IsDead() )
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
			if ( player2->IsDead() )
			{
				m_WidgetType = WIDGET_UI_IMAGE_RESULT_LOSE_FAIL;
			}
			else
			{
				m_WidgetType = WIDGET_UI_IMAGE_RESULT_LOSE_CLEAR;
			}
		}
	}


}

