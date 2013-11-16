#include "stdafx.h"
#include "RMmusicData.h"

CRMmusicData::CRMmusicData(const std::string& title,
						   const std::string& artist,
						   const std::string& level,
						   const std::string& ImageAlbum,
						   const std::string& ImageBackground,
						   const std::string& ImageShutter,
						   const std::string& ImageNote1,
						   const std::string& ImageNote2,
						   const std::string& ImageNoteEffect,
						   const std::string& SoundBackground,
						   const std::string& SoundNoteEffect1,
						   const std::string& SoundNoteEffect2,
						   const std::string& Note)
{
	m_title = title;
	m_artist = artist;
	m_level = level;
	m_ImageAlbum = ImageAlbum;
	m_ImageBackground = ImageBackground;
	m_ImageShutter = ImageShutter;
	m_ImageNote1 = ImageNote1;
	m_ImageNote2 = ImageNote2;
	m_ImageNoteEffect = ImageNoteEffect;
	m_SoundBackground = SoundBackground;
	m_SoundNoteEffect1 = SoundNoteEffect1;
	m_SoundNoteEffect2 = SoundNoteEffect2;
	m_Note = Note;
}


CRMmusicData::~CRMmusicData(void)
{
}
