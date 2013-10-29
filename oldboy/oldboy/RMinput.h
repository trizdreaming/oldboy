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
	KeyTable			GetKeyboardInput();

private:
	KeyTable			m_InputKey;
	static CRMinput*	m_pInstance;
};
