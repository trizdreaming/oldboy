#pragma once
#include <vector>
#include "RMmacro.h"
class CRMmusicSelectManager
{
	SINGLETON(CRMmusicSelectManager);

public:
	CRMmusicSelectManager(void);
	~CRMmusicSelectManager(void);

	HRESULT			ShowMusicList( const std::vector<std::string>& musicVector, const int index ) const;

private:
	std::wstring CRMmusicSelectManager::string2wstring(const std::string& str) const;
};

