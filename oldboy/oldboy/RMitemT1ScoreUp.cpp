#include "stdafx.h"
#include "RMitemT1ScoreUp.h"
#include "RMplayer1P.h"
#include "RMplayer2P.h"

CRMitemT1ScoreUp::CRMitemT1ScoreUp(void)
{
	m_WidgetType = WIDGET_ITEM_T1_SCORE_UP_GRAY;
	m_WidgetTypeForColor = WIDGET_ITEM_T1_SCORE_UP_COLOR;
	m_WidgetTypeForColorOut = WIDGET_ITEM_T1_SCORE_UP_COLOR_OUT;
	m_WidgetTypeOfCard = WIDGET_ITEM_T1_SCORE_UP_CARD;
}


CRMitemT1ScoreUp::~CRMitemT1ScoreUp(void)
{
}

void CRMitemT1ScoreUp::Active()
{
	if ( m_OwnPlayer == PLAYER_ONE )
	{
		CRMplayer1P::GetInstance()->StartScoreBoost();
	}
	else if ( m_OwnPlayer == PLAYER_TWO )
	{
		CRMplayer2P::GetInstance()->StartScoreBoost();
	}
	
	CRMitem::Active();
}

void CRMitemT1ScoreUp::DeActive()
{
	if ( m_OwnPlayer == PLAYER_ONE )
	{
		CRMplayer1P::GetInstance()->StopScoreBoost();
	}
	else if ( m_OwnPlayer == PLAYER_TWO )
	{
		CRMplayer2P::GetInstance()->StopScoreBoost();
	}

	CRMitem::DeActive();
}
