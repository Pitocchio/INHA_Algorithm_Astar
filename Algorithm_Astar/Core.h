#pragma once

class CCore
{
	SINGLETONE(CCore);

public: // LifeCycle
	void Init(HWND hWnd);
	void Progress();
	void Release();

public: // Mehod
	HWND Get_Hwnd() const { return m_Hwnd; }

private: // Variables
	RECT m_RC;
	HWND m_Hwnd;
	HDC m_Hdc;
	HBITMAP m_Hbitmap;
	HDC m_Hbitdc;
};

