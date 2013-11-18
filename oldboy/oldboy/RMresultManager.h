#pragma once
#include "RMmacro.h"
class CRMresultManager
{
	SINGLETON(CRMresultManager);

public:
	CRMresultManager(void);
	~CRMresultManager(void);

	// selectManager도 그렇고 그냥 씬들?

	void			ShowResult();

private:
	std::wstring	string2wstring(const std::string& str) const;

};

