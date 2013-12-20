#include "stdafx.h"
#include "RMchuldTitleModeSelector.h"


CRMchuldTitleModeSelector::CRMchuldTitleModeSelector(void)
{
	m_ModeIndex = 0;
	m_MaxModes = MODE_MAX - 1;
}


CRMchuldTitleModeSelector::~CRMchuldTitleModeSelector(void)
{
}

void CRMchuldTitleModeSelector::Update()
{
	SetVisibleByScene();
	
	switch ( m_ModeIndex )
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
	default:
		m_WidgetType = WIDGET_TITLE_MODE_SINGLE;
	}
}

void CRMchuldTitleModeSelector::ModeUp()
{
	m_ModeIndex += m_MaxModes;
	--m_ModeIndex %= m_MaxModes;
}

void CRMchuldTitleModeSelector::ModeDown()
{
	++m_ModeIndex %= m_MaxModes;
}

ModeType CRMchuldTitleModeSelector::GetModeType()
{
	switch ( m_ModeIndex )
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