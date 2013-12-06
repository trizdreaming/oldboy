#include "stdafx.h"
#include "RMitemT2Barrier.h"


CRMitemT2Barrier::CRMitemT2Barrier(void)
{
	m_WidgetType = WIDGET_ITEM_T2_BARRIER_GRAY;
	m_WidgetTypeForColor = WIDGET_ITEM_T2_BARRIER_COLOR;
	m_WidgetTypeOfCard = WIDGET_ITEM_T2_BARRIER_CARD;
}


CRMitemT2Barrier::~CRMitemT2Barrier(void)
{
}

void CRMitemT2Barrier::Active()
{
	m_TimeSlice = 30000;
	CRMitem::Active();
}
