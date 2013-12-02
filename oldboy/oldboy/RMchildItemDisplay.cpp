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
	m_ObjectType = CRMitemManager::GetInstance()->GetObjectType(m_ThisTier);
}
