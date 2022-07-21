#include "stdafx.h"
#include "Core.h"

CCore* CCore::m_pInst = nullptr;

void CCore::Init(HWND hWnd)
{
	// << : Double Buffering
	m_RC = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	m_Hwnd = hWnd;
	m_Hdc = GetDC(m_Hwnd);

	AdjustWindowRect(&m_RC, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(hWnd, nullptr, 100, 100, (m_RC.right - m_RC.left), (m_RC.bottom - m_RC.top), 0);

	m_Hbitmap = CreateCompatibleBitmap(m_Hdc, m_RC.right, m_RC.bottom);
	m_Hbitdc = CreateCompatibleDC(m_Hdc);

	HBITMAP hOldbit = (HBITMAP)SelectObject(m_Hbitdc, m_Hbitmap);
	DeleteObject(hOldbit);
	// >> 


	// << : Other Init
	CNodeMgr::GetInst()->Init();
	//
}

void CCore::Progress()
{

	// << : Update
	CNodeMgr::GetInst()->Update();
	CNodeMgr::GetInst()->LateUpdate();

	// >>




	// << : Render
	Rectangle(m_Hbitdc, -1, -1, m_RC.right + 1, m_RC.bottom + 1); 
	CNodeMgr::GetInst()->Render(m_Hbitdc);
	BitBlt(m_Hdc, 0, 0, m_RC.right, m_RC.bottom, m_Hbitdc, 0, 0, SRCCOPY); 

	Sleep(4000);

	// >> 
}

void CCore::Release()
{
	CNodeMgr::GetInst()->Release();
	CNodeMgr::GetInst()->DestroyInst();
}
