#include "stdafx.h"
#include "oldboy.h"
#include "RMinput.h"

CRMinput::CRMinput(void)
{
	ZeroMemory(m_PrevKeyState, sizeof(m_PrevKeyState[MAX_INPUT_KEY]));
	ZeroMemory(m_NowKeyState, sizeof(m_NowKeyState[MAX_INPUT_KEY]));

	m_KeyMap.clear();

	//SM9: 위의 키 상태 테이블은 배열이고, 여기는 맵을 이렇게 쓴 이유는? 굳이 map을 쓸 이유가 없어 보임
	//map은 레드블랙 트리로 되어 있는데, 이를 쓰는 경우는, 노드(원소)가 엄청 많은 경우 key를 통해서 값을 빨리 찾아야 하고 + for문으로 맵 전체를 순회할 경우가 필요한 경우임
	// 아래 경우는  ENUM의 수도 많지 않아서 그냥 배열로 하는게 적당해 보인다.

	m_KeyMap[KEY_TABLE_P1_ATTACK] = VK_S;
	m_KeyMap[KEY_TABLE_P1_TARGET1] = VK_A;
	m_KeyMap[KEY_TABLE_P1_TARGET2] = VK_D;
	m_KeyMap[KEY_TABLE_P2_ATTACK] = VK_DOWN;
	m_KeyMap[KEY_TABLE_P2_TARGET1] = VK_LEFT;
	m_KeyMap[KEY_TABLE_P2_TARGET2] = VK_RIGHT;
	m_KeyMap[KEY_TABLE_RETURN] = VK_RETURN;
	m_KeyMap[KEY_TABLE_ESCAPE] = VK_ESCAPE;
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
