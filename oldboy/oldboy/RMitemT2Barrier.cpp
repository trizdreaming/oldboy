#include "stdafx.h"
#include "RMitemT2Barrier.h"


CRMitemT2Barrier::CRMitemT2Barrier(void)
{
	m_ObjectType = OBJECT_ITEM_T2_BARRIER_GRAY;
	m_ObjectTypeColor = OBJECT_ITEM_T2_BARRIER_COLOR;
}


CRMitemT2Barrier::~CRMitemT2Barrier(void)
{
}

void CRMitemT2Barrier::Active()
{
	m_TimeSlice = 30000;
	CRMitem::Active();
}
