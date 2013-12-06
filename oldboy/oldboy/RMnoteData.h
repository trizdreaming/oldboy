#pragma once
#include "RMenumSet.h"

class CRMnoteData
{
public:
	CRMnoteData( int time, int level,WidgetType type );
	~CRMnoteData(void);

	int					GetTime() { return m_Time; }
	int					GetLevel() { return m_Level; }
	WidgetType			GetType() { return m_Type; }

private:
	int m_Time;
	int m_Level;
	WidgetType m_Type;
};