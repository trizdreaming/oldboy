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
	void				UpdateKeyState();
	KeyStatus			GetKeyStatusByKey( KeyTable key );

private:
	KeyStatus			m_InputKey[MAX_INPUT_KEY];

	bool				m_PrevKeyState[MAX_INPUT_KEY];
	bool				m_NowKeyState[MAX_INPUT_KEY];
};
