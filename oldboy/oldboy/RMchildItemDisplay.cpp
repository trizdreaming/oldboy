﻿#include "stdafx.h"
#include "RMchildItemDisplay.h"


CRMchildItemDisplay::CRMchildItemDisplay(void)
{
}


CRMchildItemDisplay::~CRMchildItemDisplay(void)
{
}

void CRMchildItemDisplay::Update()
{
	switch ( m_ThisTier )
	{
	case TIER_1P_ONE:
		// this->SetObjectType(OBJECT_ITEMFLAG_TIER1_)
		break;
	case TIER_1P_TWO:
		break;
	case TIER_1P_THREE:
		break;
	case TIER_2P_ONE:
		break;
	case TIER_2P_TWO:
		break;
	case TIER_2P_THREE:
		break;
	default:
		break;
	}
}