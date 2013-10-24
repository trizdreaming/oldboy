#include "stdafx.h"
#include "RMsound.h"

CRMsound* CRMsound::m_pInstance = nullptr;

CRMsound::CRMsound(void):
	m_SystemS(NULL),
	m_Sound(NULL),
	m_Channel(NULL)
{
}


CRMsound::~CRMsound(void)
{
}


// 에러 체크
void CRMsound::ERRCHECK(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		char str[256] = {0,};
		sprintf_s(str, "FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		MessageBoxA(NULL, str, "TEST", MB_OK  );
	}
}

// 팩토리 생성
void CRMsound::InitSound()
{
	FMOD_RESULT result;

	result = FMOD::System_Create(&m_SystemS);  // Create the main system object.
	ERRCHECK(result);

	result = m_SystemS->init(2, FMOD_INIT_NORMAL, 0); // Initialize FMOD.
	ERRCHECK(result);
}


// 리소스 생성 - 재생하고자 하는 음원 로딩
void CRMsound::LoadSound()
{
	FMOD_RESULT result;

	// 사운드로딩
	result = m_SystemS->createSound("./Resource/test.mp3", FMOD_LOOP_NORMAL, 0, &m_Sound);  // FMOD_DEFAULT uses the defaults.  These are the same as FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE.
	ERRCHECK(result);
}

// 재생
void CRMsound::PLAYsound()
{
	FMOD_RESULT result;
	result = m_SystemS->playSound(FMOD_CHANNEL_FREE, m_Sound, false, &m_Channel);
	m_Channel->setVolume(0.5);
	ERRCHECK(result);
}

// 해제 처리
void CRMsound::DeleteSound()
{
	if(m_Sound)
	{
		m_Sound->release();
		m_Sound = NULL;
	}
	if(m_SystemS)
	{
		m_SystemS->release();
		m_SystemS->close();
		m_SystemS = NULL;
	}
}

CRMsound* CRMsound::GetInstance()
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new CRMsound();
	}
	return m_pInstance;
}

void CRMsound::ReleaseInstance()
{
	if(m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}