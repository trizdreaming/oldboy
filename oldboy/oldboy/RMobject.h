#pragma once
class CRMobject
{
public:
	CRMobject(void);
	~CRMobject(void);

public:
	//virtual void update();
	void render();

private:
	std::wstring m_key;

	float m_xPosition;
	float m_yPosition;
	float m_width;
	float m_height;
	float m_alpha;
};

