#include "stdafx.h"
#include "RMchildItemCardDisplay.h"
#include "RMmacro.h"
#include "RMitemManager.h"


CRMchildItemCardDisplay::CRMchildItemCardDisplay(void)
{
}


CRMchildItemCardDisplay::~CRMchildItemCardDisplay(void)
{
}

void CRMchildItemCardDisplay::Update()
{
	if ( CRMitemManager::GetInstance()->GetActivatedItem(m_playerNumber) )
	{
		SetVisibleByScene();
	}

	//SetVisibleByScene();
}
