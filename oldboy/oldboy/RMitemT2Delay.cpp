#include "stdafx.h"
#include "RMitemT2Delay.h"
#include "RMnoteManager.h"


CRMitemT2Delay::CRMitemT2Delay(void)
{
	m_WidgetType = WIDGET_ITEM_T2_DELAY_GRAY;
	m_WidgetTypeForColor = WIDGET_ITEM_T2_DELAY_COLOR;
	m_WidgetTypeOfCard = WIDGET_ITEM_T2_DELAY_CARD;
}


CRMitemT2Delay::~CRMitemT2Delay(void)
{
}

void CRMitemT2Delay::Active()
{
	CRMnoteManager::GetInstance()->StartItemDelay( m_TargetPlayer );
	CRMitem::Active();
}

void CRMitemT2Delay::DeActive()
{
	CRMnoteManager::GetInstance()->StopItemDelay( m_TargetPlayer );
	CRMitem::DeActive();
}
