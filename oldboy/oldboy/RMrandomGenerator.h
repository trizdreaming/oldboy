#pragma once
#define	MAX_RANDOM_LENGTH	624
#define	BIT_MASK_32			0xffffffff

class CRMrandomGenerator
{
	SINGLETON(CRMrandomGenerator);
private:
	CRMrandomGenerator(void);
	~CRMrandomGenerator(void);

public:
	UINT	GetRandom(UINT nMin, UINT nMax);

private:
	UINT	GetRandom();
	void	Generate();
	void	Initialize();

private:
	UINT	m_Index;
	UINT	m_BitPow_31;
	std::array<UINT, MAX_RANDOM_LENGTH> m_MTState;
};
