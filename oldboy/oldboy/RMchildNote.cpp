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
	m_xPosition = static_cast<float>(static_cast<int>(++m_xPosition) % 700);
	return;
}
