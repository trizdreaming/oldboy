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
	// fmod용 함수
	HRESULT				CreateSound();
	
	HRESULT				LoadSound( const std::string& fileName, SoundType soundType );
	HRESULT				LoadPlaySound( const std::string& musicFolderName, ModeType modeType );

	void				PlaySound( SoundType soundType, bool isLoop = true );
	void				PlayEffect( SoundType soundType );
	void				PlayEffectItemUse( SoundType soundType );
	void				PlayEffectTier( SoundType soundType );

	// 사운드 일시정지를 위한 함수
	HRESULT				SetPauseBG( const bool isPause = true );

	bool				GetIsPlaying();
	UINT				GetPlayTime();

private:
	void				DeleteSound();
	HRESULT				CheckError();
	

	FMOD::System*		m_SystemS;
	FMOD::Channel*		m_ChannelBG;
	FMOD::Channel*		m_ChannelSE;
	FMOD::Channel*		m_ChannelSEItemUse;
	FMOD::Channel*		m_ChannelSETier;
	FMOD_RESULT			m_Result;

	//FMOD::Sound*	m_Sound;
	std::array<FMOD::Sound*, SOUND_MAX> m_SoundArray;
};

