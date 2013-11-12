#include "stdafx.h"
#include "RMnoteData.h"


CRMnoteData::CRMnoteData( int time, int level,ObjectType type )
{
	 m_Time=time;
	 m_Level = level;
	 m_Type = type; 
}


CRMnoteData::~CRMnoteData(void)
{
}
