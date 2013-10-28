#pragma once
#include "RMkeyMapping.h"
#include "RMenumOfKeyTable.h"

class CRMinput
{
public:
	CRMinput(void);
	~CRMinput(void);

public:
	static CRMinput* GetInstance();
	static void ReleaseInstance();

public:
	KeyTable InputKeyboard();

private:
	KeyTable m_inputKey;
	static CRMinput* m_pInstance;
};
