#include "stdafx.h"
#include "RMinput.h"

CRMinput* CRMinput::m_pInstance = nullptr;

CRMinput::CRMinput(void):
	m_inputKey(NONE)
{
}


CRMinput::~CRMinput(void)
{
}

KeyTable CRMinput::InputKeyboard()
{
	if(GetAsyncKeyState(VK_A) & 0x8000)
	{
		m_inputKey = P1TARGET1;
	}

	////////////////////////////////////
	//일단 테스트로 대문자 A키만 둠
	//키 설정을 추후 결정하도록 함

	return m_inputKey;
}

CRMinput* CRMinput::GetInstance()
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new CRMinput();
	}

	return m_pInstance;
}

void CRMinput::ReleaseInstance()
{
	if(m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}