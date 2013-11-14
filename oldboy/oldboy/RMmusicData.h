#pragma once
class CRMmusicData
{
public:
	CRMmusicData
		(
		const std::string& title,
		const std::string& artist,
		const std::string& level,
		const std::string& ImageBackground,
		const std::string& ImageShutter,
		const std::string& ImageNote1,
		const std::string& ImageNote2,
		const std::string& ImageNoteEffect,
		const std::string& SoundBackground,
		const std::string& SoundNoteEffect1,
		const std::string& SoundNoteEffect2,
		const std::string& Note
		);
	~CRMmusicData(void);

public:
	const std::string&		GetTitle() { return m_title; }
	const std::string&		GetArtist() { return m_artist; }
	const std::string&		GetLevel() { return m_level; }
	const std::string&		GetImageBackground() { return m_ImageBackground; }
	const std::string&		GetImageShutter() { return m_ImageShutter; }
	const std::string&		GetImageNote1() { return m_ImageNote1; }
	const std::string&		GetImageNote2() { return m_ImageNote2; }
	const std::string&		GetImageNoteEffect() { return m_ImageNoteEffect; }
	const std::string&		GetSoundBackground() { return m_SoundBackground; }
	const std::string&		GetSoundNoteEffect1() { return m_SoundNoteEffect1; }
	const std::string&		GetSoundNoteEffect2() { return m_SoundNoteEffect2; }
	const std::string&		GetNote() { return m_Note; }

private:
	std::string				m_title;
	std::string				m_artist;
	std::string				m_level;
	std::string				m_ImageBackground;
	std::string				m_ImageShutter;
	std::string				m_ImageNote1;
	std::string				m_ImageNote2;
	std::string				m_ImageNoteEffect;
	std::string				m_SoundBackground;
	std::string				m_SoundNoteEffect1;
	std::string				m_SoundNoteEffect2;
	std::string				m_Note;

};

