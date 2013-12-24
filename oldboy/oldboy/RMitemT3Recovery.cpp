#include "stdafx.h"
#include "RMitemT3Recovery.h"
#include "RMJudgeManager.h"


CRMitemT3Recovery::CRMitemT3Recovery(void)
{
	//////////////////////////////////////////////////////////////////////////
	// 임시 추가 - 추후 수정
	//////////////////////////////////////////////////////////////////////////
	m_WidgetType = WIDGET_ITEM_T3_RECOVERY_GRAY;
	m_WidgetTypeForColor = WIDGET_ITEM_T3_RECOVERY_COLOR;
	m_WidgetTypeForColorOut = WIDGET_ITEM_T3_RECOVERY_COLOR_OUT;
	m_WidgetTypeOfCard = WIDGET_ITEM_T3_RECOVERY_CARD;
}

CRMitemT3Recovery::~CRMitemT3Recovery(void)
{
}

void CRMitemT3Recovery::Active()
{
	CRMjudgeManager::GetInstance()->StartItemRecovery( m_OwnPlayer );
	CRMitem::Active();
}

void CRMitemT3Recovery::DeActive()
{
	CRMjudgeManager::GetInstance()->StopItemRecovery( m_OwnPlayer );
	CRMitem::DeActive();
}
