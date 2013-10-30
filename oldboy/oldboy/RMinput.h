#pragma once
#include "RMkeyMapping.h"
#include "RMenumSet.h"

class CRMinput
{
public:
	CRMinput(void);
	~CRMinput(void);

public:
	static CRMinput*	GetInstance();
	static void			ReleaseInstance();

public:
	bool*				GetKeyboardInput();

private:
	bool				m_InputKey[MAX_INPUT_KEY];
	static CRMinput*	m_pInstance;
};
