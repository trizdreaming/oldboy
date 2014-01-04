#include "stdafx.h"
#include "RMmacro.h"
#include "RMinput.h"
#include "RMpauseManager.h"
#include "RMglobalParameterManager.h"
#include "RMmainLoop.h"

CRMinput::CRMinput(void)
{
	ZeroMemory(&m_InputKey, sizeof(m_InputKey));
	ZeroMemory(&m_PrevKeyState, sizeof(m_PrevKeyState));
	ZeroMemory(&m_NowKeyState, sizeof(m_NowKeyState));
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

	// cpu모드일때는 키입력 무시 퍼스화면에서는 입력 가능
	if ( CRMpauseManager::GetInstance()->IsPause() )
	{
		return;
	}
	if ( CRMglobalParameterManager::GetInstance()->GetAirTomoMode() && CRMmainLoop::GetInstance()->GetNowScene() == SCENE_PLAY )
	{
		m_PrevKeyState[KEY_TABLE_P2_TARGET1] = false;
		m_NowKeyState[KEY_TABLE_P2_TARGET1] = false;
		m_PrevKeyState[KEY_TABLE_P2_TARGET2] = false;
		m_NowKeyState[KEY_TABLE_P2_TARGET2] = false;
		m_PrevKeyState[KEY_TABLE_P2_ATTACK] = false;
		m_NowKeyState[KEY_TABLE_P2_ATTACK] = false;
	}
}

KeyStatus CRMinput::GetKeyStatusByKey( KeyTable key ) const
{
	if ( GetActiveWindow() == NULL )
	{
		return KEY_STATUS_NOT_PRESSED;
	}
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

void CRMinput::SetVirtualKeyStatusByKey( KeyTable key )
{
	m_PrevKeyState[key] = false;
	m_NowKeyState[key] = true;
}
