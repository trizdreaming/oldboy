#include "stdafx.h"
#include "RMitemT2GaugeClear.h"
#include "RMplayer1P.h"
#include "RMplayer2P.h"

CRMitemT2GaugeClear::CRMitemT2GaugeClear(void)
{
	m_WidgetType = WIDGET_ITEM_T2_GAUGE_CLEAR_GRAY;
	m_WidgetTypeForColor = WIDGET_ITEM_T2_GAUGE_CLEAR_COLOR;
	m_WidgetTypeForColorOut = WIDGET_ITEM_T2_GAUGE_CLEAR_COLOR_OUT;
	m_WidgetTypeOfCard = WIDGET_ITEM_T2_GAUGE_CLEAR_CARD;
	m_TimeSlice = 3000;
}

CRMitemT2GaugeClear::~CRMitemT2GaugeClear(void)
{
}

void CRMitemT2GaugeClear::Active()
{
	CRMitem::Active();

	if ( m_TargetPlayer == PLAYER_ONE )
	{
		CRMplayer1P::GetInstance()->ResetMP();
	}
	if ( m_TargetPlayer == PLAYER_TWO )
	{
		CRMplayer2P::GetInstance()->ResetMP();
	}
}
