#pragma once

class CRMmusicSelectManager
{
	SINGLETON(CRMmusicSelectManager);

public:
	CRMmusicSelectManager(void);
	~CRMmusicSelectManager(void);

	//sm9: 뮤직 리스트 참조를 통째로 넘기는건 뭔가 좋은 구조가 아니다. 뮤직벡터를 누가 들고 있는게 좋을까 생각해보기 바람.. 보통 selectmanager가 직접 들고 있거나
	// 데이터 매니저 같은 놈이 들어고 있는게 정상.
	// 메인루프가 들고 있는건 좀 이상하다.

	HRESULT			ShowMusicList( const std::vector<std::string>& musicVector ) const;
	UINT			GetMusicSelectIndex() { return m_MusicSelectIndex; }
	void			SetMusicSelectIndex(const int index) { m_MusicSelectIndex = index; }
private:

	UINT			m_MusicSelectIndex;

	std::wstring	string2wstring(const std::string& str) const;
};

