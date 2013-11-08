#pragma once

class CRMmusicData;

class CRMxmlLoader
{
	SINGLETON(CRMxmlLoader);

public:
	CRMxmlLoader(void);
	~CRMxmlLoader(void);

	void		TestXML();
private:
	//           ¿Ωæ«¿Ã∏ß  ¿Ωæ«∞≥√º
	std::map<std::string, CRMmusicData*>	m_MusicDataMap;
};

