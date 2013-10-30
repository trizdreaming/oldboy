#pragma once
#include "RMkeyMapping.h"
#include "RMenumSet.h"

class CRMinput
{
	SINGLETON(CRMinput);

private:
	CRMinput(void);
	~CRMinput(void);

public:
	bool*				GetKeyboardInput();

private:
	bool				m_InputKey[MAX_INPUT_KEY];
};
