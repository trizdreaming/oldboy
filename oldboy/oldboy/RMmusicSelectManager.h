#pragma once

class CRMmusicSelectManager
{
	SINGLETON(CRMmusicSelectManager);

public:
	CRMmusicSelectManager(void);
	~CRMmusicSelectManager(void);

	HRESULT			ShowMusicList( const std::vector<std::string>& musicVector ) const;
	UINT			GetMusicSelectIndex() { return m_MusicSelectIndex; }
	void			SetMusicSelectIndex(const int index) { m_MusicSelectIndex = index; }
private:

	UINT			m_MusicSelectIndex;

	std::wstring	string2wstring(const std::string& str) const;
};

