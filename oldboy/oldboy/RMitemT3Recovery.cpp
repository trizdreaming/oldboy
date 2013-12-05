#include "stdafx.h"
#include "RMitemT3Recovery.h"
#include "RMJudgeManager.h"


CRMitemT3Recovery::CRMitemT3Recovery(void)
{
	//////////////////////////////////////////////////////////////////////////
	// 임시 추가 - 추후 수정
	//////////////////////////////////////////////////////////////////////////
	m_ObjectType = OBJECT_ITEM_T3_RECOVERY_GRAY;
	m_ObjectTypeColor = OBJECT_ITEM_T3_RECOVERY_COLOR;
}


CRMitemT3Recovery::~CRMitemT3Recovery(void)
{
}

void CRMitemT3Recovery::Active()
{
	CRMitem::Active();
	CRMjudgeManager::GetInstance()->StartItemRecovery( m_OwnPlayer );
}

void CRMitemT3Recovery::DeActive()
{
	CRMitem::DeActive();
	CRMjudgeManager::GetInstance()->StopItemRecovery( m_OwnPlayer );
}
