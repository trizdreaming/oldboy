#pragma once
#include "RMkeyMapping.h"
#include "RMenumSet.h"
#include "RMdefine.h"

class CRMinput
{
	SINGLETON(CRMinput);

private:
	CRMinput(void);
	~CRMinput(void);

public:
	void				UpdateKeyState();
	KeyStatus			GetKeyStatusByKey( KeyTable key ) const;
	void				SetVirtualKeyStatusByKey( KeyTable key );

private:
	std::array<KeyStatus, MAX_INPUT_KEY>	m_InputKey;

	std::array<bool, MAX_INPUT_KEY>			m_PrevKeyState;
	std::array<bool, MAX_INPUT_KEY>			m_NowKeyState;
};
