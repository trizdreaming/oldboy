#include "stdafx.h"
#include "RMmacro.h"
#include "RMchildItemDisplay.h"
#include "RMitemManager.h"

CRMchildItemDisplay::CRMchildItemDisplay(void)
{
}

CRMchildItemDisplay::~CRMchildItemDisplay(void)
{
}

void CRMchildItemDisplay::Update()
{
	SetVisibleByScene();

	m_ObjectType = CRMitemManager::GetInstance()->GetObjectType(m_ThisTier);
	m_PositionY = CRMitemManager::GetInstance()->GetStackPosition(m_ThisTier);

	// printConsole("티어 : %d, 오브젝트 타입 : %d, 좌표 : (%f, %f) \n", m_ThisTier, m_ObjectType, m_PositionX, m_PositionY);
}
