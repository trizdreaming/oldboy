#include "stdafx.h"
#include "oldboy.h"
#include "RMinput.h"

CRMinput* CRMinput::m_pInstance = nullptr;

CRMinput::CRMinput(void):
	m_InputKey(NO_INPUT)
{
}


CRMinput::~CRMinput(void)
{
}

KeyTable CRMinput::GetKeyboardInput()
{
	m_InputKey = NO_INPUT;
	// 여기 초기화 부분이 빠져서 추가함

	if ( GetAsyncKeyState(VK_A) & 0x8000 )
	{
		m_InputKey = P1TARGET1;
	}

	////////////////////////////////////
	//일단 테스트로 대문자 A키만 둠
	//키 설정을 추후 결정하도록 함

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