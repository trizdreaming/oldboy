#include "stdafx.h"
#include "oldboy.h"
#include "RMinput.h"

CRMinput::CRMinput(void)
{
	ZeroMemory(m_PrevKeyState, sizeof(m_PrevKeyState[MAX_INPUT_KEY]));
	ZeroMemory(m_NowKeyState, sizeof(m_NowKeyState[MAX_INPUT_KEY]));

	m_KeyMap.clear();
	m_KeyMap[P1_ATTACK] = VK_S;
	m_KeyMap[P1_TARGET1] = VK_A;
	m_KeyMap[P1_TARGET2] = VK_D;
	m_KeyMap[P2_ATTACK] = VK_DOWN;
	m_KeyMap[P2_TARGET1] = VK_LEFT;
	m_KeyMap[P2_TARGET2] = VK_RIGHT;
	m_KeyMap[KEY_RETURN] = VK_RETURN;
	m_KeyMap[KEY_ESCAPE] = VK_ESCAPE;
}


CRMinput::~CRMinput(void)
{
}

void CRMinput::UpdateKeyState()
{
	for ( int i = 0 ; i < MAX_INPUT_KEY ; i++ )
	{
		m_PrevKeyState[i] = m_NowKeyState[i];

		if( !m_KeyMap[ (KeyTable) i ] )
			continue;

		if( GetAsyncKeyState( m_KeyMap[ (KeyTable) i ] ) & 0x8000 )
		{
			m_NowKeyState[i] = true;
		}
		else
		{
			m_NowKeyState[i] = false;
		}
	}
}

KeyStatus CRMinput::GetKeyStatusByKey( KeyTable key )
{
	if ( m_PrevKeyState[key] == false && m_NowKeyState[key] == true )
	{
		return KEY_DOWN;
	}
	else if ( m_PrevKeyState[key] == true && m_NowKeyState[key] == true )
	{
		return KEY_PRESSED;
	}
	else if ( m_PrevKeyState[key] == true && m_NowKeyState[key] == false )
	{
		return KEY_UP;
	}

	return KEY_NOTPRESSED;
}
