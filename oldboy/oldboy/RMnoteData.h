#pragma once
#include "RMenumSet.h"

class CRMnoteData
{
public:
	CRMnoteData( int time, int level,ObjectType type );
	~CRMnoteData(void);

	int					GetTime() { return m_Time; }
	int					GetLevel() { return m_Level; }
	ObjectType			GetType() { return m_Type; }

private:
	int m_Time;
	int m_Level;
	ObjectType m_Type;
};