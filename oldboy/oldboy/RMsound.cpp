#include "stdafx.h"
#include "RMsound.h"

CRMsound* CRMsound::m_pInstance = nullptr;

CRMsound::CRMsound(void):
	m_SystemS(nullptr),
	m_Channel(nullptr),
	m_Result(FMOD_ERR_UNINITIALIZED)
{
}


CRMsound::~CRMsound(void)
{
	// 소멸자에서 할당한 자원을 반납하도록 함
	DeleteSound();
}


// 에러 체크
void CRMsound::ErrorCheck()
{
	if (m_Result != FMOD_OK)
	{
		TCHAR str[256] = {0,};
		wprintf_s(str, L"FMOD error! (%d) %s\n", m_Result, FMOD_ErrorString(m_Result));
		MessageBox(NULL, str, L"TEST", MB_OK  );
	}
}

// 팩토리 생성
void CRMsound::InitSound()
{
	m_Result = FMOD::System_Create(&m_SystemS);  // Create the main system object.
	ErrorCheck();

	if(m_Result == FMOD_OK)
	{
		m_Result = m_SystemS->init(2, FMOD_INIT_NORMAL, 0); // Initialize FMOD.
		ErrorCheck();
	}
}


// 리소스 생성 - 재생하고자 하는 음원 로딩
void CRMsound::LoadSound(std::string fileName)
{
	// 사운드로딩
	if(m_Result == FMOD_OK)
	{
		FMOD::Sound* m_Sound;
		std::string filePath = "./Resource/"+fileName;
		m_Result = m_SystemS->createSound(filePath.c_str(), FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &m_Sound);  // FMOD_DEFAULT uses the defaults.  These are the same as FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE.
		ErrorCheck();
		m_SoundMap[fileName] = m_Sound;
	}
}

// 재생
void CRMsound::PLAYsound(std::string fileName)
{
	if(m_Result == FMOD_OK)
	{
		m_Channel->stop();
		m_Result = m_SystemS->playSound(FMOD_CHANNEL_FREE, m_SoundMap[fileName], false, &m_Channel);
		m_Channel->setVolume(0.5);
		m_Channel->setMode(FMOD_LOOP_NORMAL);
		ErrorCheck();
	}
}

// 효과음 재생
void CRMsound::PLAYSEsound(std::string fileName)
{
	if(m_Result == FMOD_OK)
	{
		
		m_Result = m_SystemS->playSound(FMOD_CHANNEL_FREE, m_SoundMap[fileName], false, &m_Channel);
		m_Channel->setVolume(0.5);
		ErrorCheck();
	}
}


// 해제 처리
void CRMsound::DeleteSound()
{

	for(auto &iter = m_SoundMap.begin(); iter != m_SoundMap.end(); ++iter)
	{
		iter->second->release(); // m_Sound
	}
	m_SoundMap.clear();

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

