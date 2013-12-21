#pragma once
#include "RMmacro.h"

class CRMmusicData;
class CRMnoteData;

class CRMxmlLoader
{
	SINGLETON(CRMxmlLoader);


public:
	HRESULT				LoadMusicData( const std::string& folderName );
	HRESULT				LoadNoteData( const std::string& folderName );
	CRMnoteData*		GetNoteByIndex( const UINT index );

	CRMmusicData*		GetMusicData( const std::string& folderName ) { return m_MusicDataMap[folderName]; }
private:
	CRMxmlLoader(void);
	~CRMxmlLoader(void);

	//           폴더이름  음악개체
	std::map<std::string, CRMmusicData*>	m_MusicDataMap;
	std::vector<CRMnoteData*>					m_NoteList;
};
