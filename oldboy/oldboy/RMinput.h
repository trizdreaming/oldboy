#pragma once
#include "RMkeyMapping.h"

enum KeyTable
{
	NO_INPUT,

	ESCAPE,

	P1TARGET1,
	P1TARGET2,
	P1ATTACK,

	P2TARGET1,
	P2TARGET2,
	P2ATTACK
};

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
