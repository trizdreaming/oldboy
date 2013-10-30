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
	
	void				LoadSound( const std::string& fileName );
	void				PlaySound( const std::string& fileName );
	void				PlayEffect( const std::string& fileName );
	
private:
	void				DeleteSound();
	void				CheckError();
	

	FMOD::System*		m_SystemS;
	FMOD::Channel*		m_Channel;
	FMOD_RESULT			m_Result;

	//FMOD::Sound*	m_Sound;
	std::map<std::string, FMOD::Sound*>	m_SoundMap;
};

