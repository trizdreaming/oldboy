#include "stdafx.h"
#include "RMitemT1Duplicate.h"
#include "RMnoteManager.h"


CRMitemT1Duplicate::CRMitemT1Duplicate(void)
{
	m_WidgetType = WIDGET_ITEM_T1_DUPLICATE_GRAY;
	m_WidgetTypeForColor = WIDGET_ITEM_T1_DUPLICATE_COLOR;
	m_WidgetTypeOfCard = WIDGET_ITEM_T1_DUPLICATE_CARD;
	m_TimeSlice = 1500;
}


CRMitemT1Duplicate::~CRMitemT1Duplicate(void)
{
}

void CRMitemT1Duplicate::Active()
{
	CRMnoteManager::GetInstance()->StartItemDuplicate( m_TargetPlayer );
	CRMitem::Active();
}

void CRMitemT1Duplicate::DeActive()
{
	CRMnoteManager::GetInstance()->StopItemDuplicate( m_TargetPlayer );
	CRMitem::DeActive();
}
