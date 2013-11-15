#include "stdafx.h"
#include "RMmacro.h"
#include "RMinput.h"

CRMinput::CRMinput(void)
{
	ZeroMemory(m_PrevKeyState, sizeof(m_PrevKeyState[MAX_INPUT_KEY]));
	ZeroMemory(m_NowKeyState, sizeof(m_NowKeyState[MAX_INPUT_KEY]));
}


CRMinput::~CRMinput(void)
{
}

void CRMinput::UpdateKeyState()
{
	for ( int i = 0 ; i < MAX_INPUT_KEY ; i++ )
	{
		m_PrevKeyState[i] = m_NowKeyState[i];

		if( GetAsyncKeyState( i ) & 0x8000 )
		{
			m_NowKeyState[i] = true;
		}
		else
		{
			m_NowKeyState[i] = false;
		}
	}
}

KeyStatus CRMinput::GetKeyStatusByKey( KeyTable key ) const
{
	if ( m_PrevKeyState[key] == false && m_NowKeyState[key] == true )
	{
		return KEY_STATUS_DOWN;
	}
	else if ( m_PrevKeyState[key] == true && m_NowKeyState[key] == true )
	{
		return KEY_STATUS_PRESSED;
	}
	else if ( m_PrevKeyState[key] == true && m_NowKeyState[key] == false )
	{
		return KEY_STATUS_UP;
	}

	return KEY_STATUS_NOT_PRESSED;
}
