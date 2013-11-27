#pragma once
class CRMmusicData
{
public:
	CRMmusicData(void);
	~CRMmusicData(void);

public:
	const std::string&		GetTitle() { return m_Title; }
	const std::string&		GetArtist() { return m_Artist; }
	const std::string&		GetLevel() { return m_Level; }
	const std::string&		GetImageAlbum() { return m_ImageAlbum; }
	const std::string&		GetImageBackground() { return m_ImageBackground; }
	const std::string&		GetImageShutter() { return m_ImageShutter; }
	const std::string&		GetImageNote1() { return m_ImageNote1; }
	const std::string&		GetImageNote2() { return m_ImageNote2; }
	const std::string&		GetImageNoteEffect() { return m_ImageNoteEffect; }
	const std::string&		GetSoundBackground() { return m_SoundBackground; }
	const std::string&		GetSoundNoteEffect1() { return m_SoundNoteEffect1; }
	const std::string&		GetSoundNoteEffect2() { return m_SoundNoteEffect2; }
	const std::string&		GetNote() { return m_Note; }


	void		SetTitle( const std::string& title ) { m_Title = title; }
	void		SetArtist( const std::string& artist ) { m_Artist = artist; }
	void		SetLevel( const std::string& level ) { m_Level = level; }
	void		SetImageAlbum( const std::string& ImageAlbum ) { m_ImageAlbum = ImageAlbum; }
	void		SetImageBackground( const std::string& ImageBackground ) { m_ImageBackground = ImageBackground; }
	void		SetImageShutter( const std::string& ImageShutter ) { m_ImageShutter = ImageShutter; }
	void		SetImageNote1( const std::string& ImageNote1 ) { m_ImageNote1 = ImageNote1; }
	void		SetImageNote2( const std::string& ImageNote2 ) { m_ImageNote2 = ImageNote2; }
	void		SetImageNoteEffect( const std::string& ImageNoteEffect ) { m_ImageNoteEffect = ImageNoteEffect; }
	void		SetSoundBackground( const std::string& soundBackground ) { m_SoundBackground = soundBackground; }
	void		SetSoundNoteEffect1( const std::string& soundNoteEffect1 ) { m_SoundNoteEffect1 = soundNoteEffect1; }
	void		SetSoundNoteEffect2( const std::string& soundNoteEffect2 ) { m_SoundNoteEffect2 = soundNoteEffect2; }
	void		SetNote( const std::string& note ) { m_Note = note; }

private:
	std::string				m_Title;
	std::string				m_Artist;
	std::string				m_Level;
	std::string				m_ImageAlbum;
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

