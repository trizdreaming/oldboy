#include "stdafx.h"
#include "RMchildNote.h"


CRMchildNote::CRMchildNote(void)
{
}


CRMchildNote::~CRMchildNote(void)
{
}

void CRMchildNote::Update()
{
	CRMobject::Update();

	if(m_PositionY >= 0)
	{
		m_PositionY = static_cast<float>(static_cast<int>(m_PositionY + 5) % 660);
	}
	else
	{
		m_PositionY += 5;
	}
	
	return;
}
