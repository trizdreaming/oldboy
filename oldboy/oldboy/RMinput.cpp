#include "stdafx.h"
#include "oldboy.h"
#include "RMinput.h"

CRMinput* CRMinput::m_pInstance = nullptr;

CRMinput::CRMinput(void)
{
	ZeroMemory(m_InputKey, sizeof(m_InputKey[MAX_INPUT_KEY]));
}


CRMinput::~CRMinput(void)
{
}

bool* CRMinput::GetKeyboardInput()
{
	ZeroMemory(m_InputKey, sizeof(m_InputKey[MAX_INPUT_KEY]));

	if ( GetAsyncKeyState(VK_A) & 0x8000 )
	{
		m_InputKey[P1_TARGET1] = true;
	}

	if ( GetAsyncKeyState(VK_S) & 0x8000 )
	{
		m_InputKey[P1_ATTACK] = true;
	}

	if ( GetAsyncKeyState(VK_D) & 0x8000 )
	{
		m_InputKey[P1_TARGET2] = true;
	}

	if ( GetAsyncKeyState(VK_LEFT) & 8000 )
	{
		m_InputKey[P2_TARGET1] = true;
	}

	if ( GetAsyncKeyState(VK_DOWN) & 8000 )
	{
		m_InputKey[P2_ATTACK] = true;
	}

	if ( GetAsyncKeyState(VK_RIGHT) & 8000 )
	{
		m_InputKey[P2_TARGET2] = true;
	}

	return m_InputKey;
}

CRMinput* CRMinput::GetInstance()
{
	if ( m_pInstance == nullptr )
	{
		m_pInstance = new CRMinput();
	}

	return m_pInstance;
}

void CRMinput::ReleaseInstance()
{
	if ( m_pInstance != nullptr )
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}