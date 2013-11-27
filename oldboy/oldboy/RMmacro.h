#pragma  once

template <typename T>
inline void SafeRelease(T* &p)
{
	if(p != nullptr)
	{
		p->Release();
		p = nullptr;
	}
}


template <typename T>
inline void SafeDelete(T* &p)
{
	if(p != nullptr)
	{
		delete p;
		p = nullptr;
	}
}

#define SINGLETON(type) \
	public: \
	static type* GetInstance() { static type s; return &s; }

#ifdef _DEBUG
#define printConsole( c, ... ) printf_s( c, ##__VA_ARGS__ )
#else
#define printConsole( c, ... )
#endif // !_DEBUG
