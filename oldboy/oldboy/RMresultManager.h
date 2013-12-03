#pragma once
#include "RMmacro.h"
class CRMresultManager
{
	SINGLETON(CRMresultManager);

public:
	CRMresultManager(void);
	~CRMresultManager(void);

	// selectManager도 그렇고 그냥 씬들? //sm9: 보통 화면 바뀌면 씬으로 분리...

	void			ShowResult();

private:
	std::wstring	string2wstring(const std::string& str) const;

};

