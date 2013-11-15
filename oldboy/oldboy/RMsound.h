#pragma once
#include "RMenumSet.h"
#include "LibraryFmod/fmod.h"
#include "LibraryFmod/fmod.hpp"
#include "LibraryFmod/fmod_errors.h"

class CRMsound
{
	SINGLETON(CRMsound);

private:
	CRMsound(void);
	~CRMsound(void);

public:
	// fmod¿ë ÇÔ¼ö
	HRESULT				CreateSound();
	
	HRESULT				LoadSound( const std::string& fileName, SoundType soundType );
	HRESULT				LoadPlaySound( const std::string& musicFolderName );

	void				PlaySound( SoundType soundType, bool isLoop = true );
	void				PlayEffect( SoundType soundType );
	
private:
	void				DeleteSound();
	HRESULT				CheckError();
	

	FMOD::System*		m_SystemS;
	FMOD::Channel*		m_ChannelBG;
	FMOD::Channel*		m_ChannelSE;
	FMOD_RESULT			m_Result;

	//FMOD::Sound*	m_Sound;
	std::map<SoundType, FMOD::Sound*>	m_SoundMap;
};

