#pragma once

class CRMmusicData;
class CRMnoteData;

class CRMxmlLoader
{
	SINGLETON(CRMxmlLoader);


public:
	CRMxmlLoader(void);
	~CRMxmlLoader(void);
	
	HRESULT				LoadMusicData( const std::string& folderName );
	HRESULT				LoadNoteData( const std::string& folderName );
	CRMnoteData*		GetNoteByIndex( const UINT index );

	CRMmusicData*		GetMusicData( const std::string& folderName ) { return m_MusicDataMap[folderName]; }
private:
	//           폴더이름  음악개체
	std::map<std::string, CRMmusicData*>	m_MusicDataMap;
	std::vector<CRMnoteData*>					m_NoteList;
};
