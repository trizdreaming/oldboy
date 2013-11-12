#pragma once

class CRMmusicData;

class CRMxmlLoader
{
	SINGLETON(CRMxmlLoader);

public:
	CRMxmlLoader(void);
	~CRMxmlLoader(void);
	
	void				LoadMusicData(const std::string& folderName );
	CRMmusicData*		GetMusicData(const std::string& folderName ) { return m_MusicDataMap[folderName]; } //SM9: 이렇게 const 써야겠지?
private:
	//           폴더이름  음악개체
	std::map<std::string, CRMmusicData*>	m_MusicDataMap;
};

