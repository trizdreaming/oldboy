#pragma once

class CRMsound
{
	SINGLETON(CRMsound);

private:
	CRMsound(void);
	~CRMsound(void);

public:
	// fmod¿ë ÇÔ¼ö
	void				CreateSound();
	
	void				LoadSound( const std::string& fileName, SoundType soundType );
	void				LoadPlaySound( const std::string& musicFolderName );

	void				PlaySound( SoundType soundType );
	void				PlayEffect( SoundType soundType );
	
private:
	void				DeleteSound();
	void				CheckError();
	

	FMOD::System*		m_SystemS;
	FMOD::Channel*		m_Channel;
	FMOD_RESULT			m_Result;

	//FMOD::Sound*	m_Sound;
	std::map<SoundType, FMOD::Sound*>	m_SoundMap;
};

