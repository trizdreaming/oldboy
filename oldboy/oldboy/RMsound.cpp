#include "stdafx.h"
#include "RMdefine.h"
#include "RMconst.h"
#include "RMmacro.h"
#include "RMsound.h"
#include "RMxmlLoader.h"
#include "RMmusicData.h"

CRMsound::CRMsound(void):
	m_SystemS(nullptr),
	m_ChannelBG(nullptr),
	m_ChannelSE(nullptr),
	m_ChannelSEItemUse(nullptr),
	m_ChannelSETier(nullptr),
	m_Result(FMOD_ERR_UNINITIALIZED)
{
	ZeroMemory(&m_SoundArray, sizeof(m_SoundArray));
}


CRMsound::~CRMsound(void)
{
	// 소멸자에서 할당한 자원을 반납하도록 함
	DeleteSound();

	if ( m_SystemS )
	{
		m_SystemS->release();
		m_SystemS->close();
		m_SystemS = NULL;
	}
}


// 에러 체크
HRESULT CRMsound::CheckError()
{
	if ( m_Result != FMOD_OK )
	{
		printConsole( ERROR_FMOD_CONSOLE, m_Result, FMOD_ErrorString( m_Result ) );

		return S_FALSE;
	}

	return S_OK;
}

// 팩토리 생성
HRESULT CRMsound::CreateSound()
{
	m_Result = FMOD::System_Create(&m_SystemS);  // Create the main system object.
	
	if ( CheckError() != S_OK )
	{
		return S_FALSE;
	}
	
	m_Result = m_SystemS->init(64, FMOD_INIT_NORMAL, 0); // Initialize FMOD.
		
	if ( CheckError() != S_OK )
	{
		return S_FALSE;
	}
	
	return S_OK;
}


// 실제 리소스 생성
// 파일 위치과, 현재 장면에 맞는 타입(enum)을 적어줌으로써 확인
HRESULT CRMsound::LoadSound( const std::string& filePath, SoundType soundType )
{
	if ( CheckError() != S_OK )
	{
		return S_FALSE;
	}
	
	FMOD::Sound* m_Sound;

	m_Result = m_SystemS->createSound(filePath.c_str(), FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &m_Sound);
	// FMOD_DEFAULT uses the defaults.  These are the same as FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE.
	
	if ( CheckError() != S_OK )
	{
		return S_FALSE;
	}

	m_SoundArray[soundType] = m_Sound;
	return S_OK;
}

// 곡에 맞춰 폴더의 음악을 로딩
HRESULT CRMsound::LoadPlaySound( const std::string& musicFolderName )
{
	HRESULT hr = S_FALSE;

	DeleteSound();

	std::string filePath;
	hr = LoadSound( BGM_TITLE, SOUND_BG_TITLE );
	if ( CheckError() != S_OK )
	{
		DeleteSound();
		return hr;
	}

	hr = LoadSound( BGM_RESULT, SOUND_BG_RESULT );
	if ( CheckError() != S_OK )
	{
		DeleteSound();
		return hr;
	}

	hr = LoadSound( SE_SELECT_MUSIC_CALL, SOUND_EFFECT_SELECT_MUSIC_CALL );
	if ( CheckError() != S_OK )
	{
		DeleteSound();
		return hr;
	}

	hr = LoadSound( SE_SELECT_MUSIC_FLIP, SOUND_EFFECT_SELECT_MUSIC_FLIP );
	if ( CheckError() != S_OK )
	{
		DeleteSound();
		return hr;
	}

	hr = LoadSound( SE_SELECT_MUSIC_START, SOUND_EFFECT_SELECT_MUSIC_START );
	if ( CheckError() != S_OK )
	{
		DeleteSound();
		return hr;
	}

	hr = LoadSound( SE_RESULT_CLEAR, SOUND_EFFECT_RESULT_CLEAR );
	if ( CheckError() != S_OK )
	{
		DeleteSound();
		return hr;
	}

	hr = LoadSound( SE_RESULT_FAIL, SOUND_EFFECT_RESULT_FAIL );
	if ( CheckError() != S_OK )
	{
		DeleteSound();
		return hr;
	}

	hr = LoadSound( SE_RESULT_FULLCOMBO, SOUND_EFFECT_RESULT_FULLCOMBO );
	if ( CheckError() != S_OK )
	{
		DeleteSound();
		return hr;
	}

	hr = LoadSound( SE_PAUSE_CANCEL, SOUND_EFFECT_PAUSE_CANCEL );
	if ( CheckError() != S_OK )
	{
		DeleteSound();
		return hr;
	}

	hr = LoadSound( SE_PAUSE_FLIP, SOUND_EFFECT_PAUSE_FLIP );
	if ( CheckError() != S_OK )
	{
		DeleteSound();
		return hr;
	}

	hr = LoadSound( SE_PAUSE_OK, SOUND_EFFECT_PAUSE_OK );
	if ( CheckError() != S_OK )
	{
		DeleteSound();
		return hr;
	}

	hr = LoadSound( SE_PAUSE_OPEN, SOUND_EFFECT_PAUSE_OPEN );
	if ( CheckError() != S_OK )
	{
		DeleteSound();
		return hr;
	}

	hr = LoadSound( SE_PLAY_ITEM_ATTACK, SOUND_EFFECT_PLAY_ITEM_ATTACK );
	if ( CheckError() != S_OK )
	{
		DeleteSound();
		return hr;
	}

	hr = LoadSound( SE_PLAY_ITEM_HEAL, SOUND_EFFECT_PLAY_ITEM_HEAL );
	if ( CheckError() != S_OK )
	{
		DeleteSound();
		return hr;
	}

	hr = LoadSound( SE_PLAY_TIER1_FULL, SOUND_EFFECT_PLAY_TIER1_FULL );
	if ( CheckError() != S_OK )
	{
		DeleteSound();
		return hr;
	}

	hr = LoadSound( SE_PLAY_TIER2_FULL, SOUND_EFFECT_PLAY_TIER2_FULL );
	if ( CheckError() != S_OK )
	{
		DeleteSound();
		return hr;
	}

	hr = LoadSound( SE_PLAY_TIER3_FULL, SOUND_EFFECT_PLAY_TIER3_FULL );
	if ( CheckError() != S_OK )
	{
		DeleteSound();
		return hr;
	}

	hr = LoadSound( SE_PLAY_DANGER_SIREN1, SOUND_EFFECT_PLAY_DANGER_SIREN1 );
	if ( CheckError() != S_OK )
	{
		DeleteSound();
		return hr;
	}

	hr = LoadSound( SE_PLAY_SHUTTER_DOWN, SOUND_EFFECT_PLAY_SHUTTER_DOWN );
	if ( CheckError() != S_OK )
	{
		DeleteSound();
		return hr;
	}

	hr = LoadSound( SE_PLAY_50_COMBO, SOUND_EFFECT_PLAY_50_COMBO );
	if ( CheckError() != S_OK )
	{
		DeleteSound();
		return hr;
	}

	hr = LoadSound( SE_PLAY_100_COMBO, SOUND_EFFECT_PLAY_100_COMBO );
	if ( CheckError() != S_OK )
	{
		DeleteSound();
		return hr;
	}

	filePath = MUSIC_FOLDER;
	filePath.append( musicFolderName );
	filePath.append( FOLDER_SLASH );
	filePath.append( CRMxmlLoader::GetInstance()->GetMusicData( musicFolderName )->GetSoundBackground() );
	hr = LoadSound( filePath, SOUND_BG_PLAY );
	if ( CheckError() != S_OK )
	{
		DeleteSound();
		return hr;
	}

	filePath = MUSIC_FOLDER;
	filePath.append(musicFolderName);
	filePath.append(FOLDER_SLASH);
	filePath.append( CRMxmlLoader::GetInstance()->GetMusicData( musicFolderName )->GetSoundNoteEffect1() );
	hr = LoadSound( filePath, SOUND_NOTE_1 );
	if ( CheckError() != S_OK )
	{
		DeleteSound();
		return hr;
	}

	filePath = MUSIC_FOLDER;
	filePath.append( musicFolderName );
	filePath.append( FOLDER_SLASH );
	filePath.append( CRMxmlLoader::GetInstance()->GetMusicData( musicFolderName )->GetSoundNoteEffect2() );
	hr = LoadSound( filePath, SOUND_NOTE_2 );
	if ( CheckError() != S_OK )
	{
		DeleteSound();
		return hr;
	}

	return hr;
}

// 재생
void CRMsound::PlaySound( SoundType soundType, bool isLoop )
{
	if ( m_Result == FMOD_OK )
	{

		if ( m_ChannelBG != nullptr )
		{
			m_ChannelBG->stop();
		}
		
		m_Result = m_SystemS->playSound( FMOD_CHANNEL_FREE, m_SoundArray[soundType], false, &m_ChannelBG );
		m_ChannelBG->setVolume(0.8f);
		if (isLoop)
		{
			m_ChannelBG->setMode( FMOD_LOOP_NORMAL );
		}
		else
		{
			m_ChannelBG->setMode( FMOD_LOOP_OFF );
		}
		
		CheckError();
	}
}

// 효과음 재생
void CRMsound::PlayEffect( SoundType soundType )
{
	if ( m_Result == FMOD_OK )
	{
		m_Result = m_SystemS->playSound( FMOD_CHANNEL_FREE, m_SoundArray[soundType], false, &m_ChannelSE );
		m_ChannelSE->setVolume( 0.7f );
		CheckError();
	}
}

// 효과음 재생2
void CRMsound::PlayEffectItemUse( SoundType soundType )
{
	if ( m_Result == FMOD_OK )
	{
		m_Result = m_SystemS->playSound( FMOD_CHANNEL_FREE, m_SoundArray[soundType], false, &m_ChannelSEItemUse );
		m_ChannelSEItemUse->setVolume( 1.0f );
		CheckError();
	}
}

void CRMsound::PlayEffectTier( SoundType soundType )
{
	if ( m_Result == FMOD_OK )
	{
		m_Result = m_SystemS->playSound( FMOD_CHANNEL_FREE, m_SoundArray[soundType], false, &m_ChannelSETier );
		m_ChannelSETier->setVolume( 1.0f );
		CheckError();
	}
}

// 해제 처리
void CRMsound::DeleteSound()
{
	for ( auto& toBeDelete : m_SoundArray )
	{
		toBeDelete->release(); // m_Sound
	}

}

bool CRMsound::GetIsPlaying()
{
	unsigned int nowTime = 0;
	unsigned int fullTime = 0;

	m_SoundArray[SOUND_BG_PLAY]->getLength(&fullTime,FMOD_TIMEUNIT_MS);
	m_ChannelBG->getPosition(&nowTime,FMOD_TIMEUNIT_MS);

	if ( nowTime >= fullTime )
	{
		return false;
	}
	return true;
}

HRESULT CRMsound::SetPauseBG( const bool isPause /*= true */ )
{
	m_Result = m_ChannelBG->setPaused( isPause );

	if ( m_Result == FMOD_OK )
	{
		return S_OK;
	}
	return S_FALSE;
}

UINT CRMsound::GetPlayTime()
{
	UINT nowTime = 0;

	if ( m_Result == FMOD_OK )
	{
		m_ChannelBG->getPosition( &nowTime , FMOD_TIMEUNIT_MS );
	}

	if ( m_Result == FMOD_OK )
	{
		return nowTime;
	}

	return 0;
}
