#include "stdafx.h"
#include "RMchuldTitleModeSelector.h"


CRMchuldTitleModeSelector::CRMchuldTitleModeSelector(void)
{
	printConsole("#######\n");
	printConsole("#######\n");
	printConsole("#######\n");
	printConsole("#######\n");

	m_ModeIndex = 0;
	m_MaxModes = MODE_MAX - 1;
}


CRMchuldTitleModeSelector::~CRMchuldTitleModeSelector(void)
{
}

void CRMchuldTitleModeSelector::Update()
{

	SetVisibleByScene();
	printConsole("Idx-%d\n", CRMchuldTitleModeSelector::GetInstance()->GetIndex());
	int mode = CRMchuldTitleModeSelector::GetInstance()->GetIndex() % m_MaxModes;
	
	switch ( mode )
	{
	case 0:
		m_WidgetType = WIDGET_TITLE_MODE_SINGLE;
		break;
	case 1:
		m_WidgetType = WIDGET_TITLE_MODE_DUAL;
		break;
	case 2:
		m_WidgetType = WIDGET_TITLE_MODE_TUTORIAL;
		break;
	case 3:
		m_WidgetType = WIDGET_TITLE_MODE_EXIT;
		break;
	}

}

void CRMchuldTitleModeSelector::ModeUp()
{
	printConsole("KEY-Idx-%d\n", m_ModeIndex);
	
	m_ModeIndex += m_MaxModes;
	--m_ModeIndex;
}

void CRMchuldTitleModeSelector::ModeDown()
{
	++m_ModeIndex;
}

ModeType CRMchuldTitleModeSelector::GetModeType()
{
	int mode = m_ModeIndex % m_MaxModes;

	switch ( mode )
	{
	case 0:
		return MODE_SINGLE;
	case 1:
		return MODE_DUAL;
	case 2:
		return MODE_TUTORIAL;
	case 3:
		return MODE_EXIT;
	}

	return MODE_NONE;
}

UINT CRMchuldTitleModeSelector::GetIndex()
{
	return m_ModeIndex;
}
