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
	void			DrawLabel( int offsetX, int offsetY, float R, float G, float B, int drawNum ) const;
	std::wstring	string2wstring(const std::string& str) const;
	
};

