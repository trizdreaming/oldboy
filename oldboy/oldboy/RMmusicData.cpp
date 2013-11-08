#include "stdafx.h"
#include "RMmusicData.h"


CRMmusicData::CRMmusicData(std::string title,
						   std::string artist,
						   std::string level,
						   std::string ImageBackground,
						   std::string ImageShutter,
						   std::string ImageNote1,
						   std::string ImageNote2,
						   std::string ImageNoteEffect,
						   std::string SoundBackground,
						   std::string SoundNoteEffect1,
						   std::string SoundNoteEffect2,
						   std::string Note)
{
	m_title = title;
	m_artist = artist;
	m_level = level;
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
