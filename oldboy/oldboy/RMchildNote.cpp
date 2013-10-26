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
	if(m_yPosition >= 0)
	{
		m_yPosition = static_cast<float>(static_cast<int>(m_yPosition + 5) % 660);
	}
	else
	{
		m_yPosition += 5;
	}
	
	return;
}
