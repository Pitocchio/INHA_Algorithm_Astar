#include "stdafx.h"
#include "NodeMgr.h"

CNodeMgr* CNodeMgr::m_pInst = nullptr;

void CNodeMgr::Init()
{
	// 전체 타일 세팅 
	int n = 0;
	
	for (int i = 0; i < TILE_ROW; ++i)
	{
		for (int j = 0; j < TILE_COL; ++j)
		{
			Node* N = new Node();
			N->Pos.x = TILE_CWIDTH * j;
			N->Pos.y = TILE_CHEIGHT * i;
			N->Num = n++;

			m_listTile[i][j] = N;
		}
	}

	// 알고리즘 구현 후, 마우스 입력으로 바꾸자
	m_listTile[5][5]->Nodetype = NODE_TYPE::START;
	m_listTile[21][23]->Nodetype = NODE_TYPE::END;
	
	m_PQ.push(m_listTile[5][5]);
}

void CNodeMgr::Update()
{
	
	while (!m_PQ.empty()) 
	{

		Node* N = m_PQ.top(); 

		if (N->Nodetype == NODE_TYPE::END)
			break;

		Set_SurrNode(N);


	}


	
}

void CNodeMgr::Set_SurrNode(Node* N) // N 주변 8개 노드를 찾아 G와 H를 세팅
{
	for (int i = 0; i < TILE_ROW; ++i)
	{
		for (int j = 0; j < TILE_COL; ++j)
		{
			if (m_listTile[i][j]->Num == N->Num)
			{
				m_listTile[i - 1][j]->G += 10;
				m_listTile[i + 1][j]->G += 10;
				m_listTile[i][j + 1]->G += 10;
				m_listTile[i][j - 1]->G += 10;


				m_listTile[i - 1][j + 1]->G += 14;
				m_listTile[i + 1][j + 1]->G += 14;
				m_listTile[i - 1][j - 1]->G += 14;
				m_listTile[i + 1][j - 1]->G += 14;


			}
		}
	}


}


void CNodeMgr::LateUpdate()
{
}

void CNodeMgr::Render(HDC hdc)
{
	for (int i = 0; i < TILE_ROW; ++i)
	{
		for (int j = 0; j < TILE_COL; ++j)
		{
			if (m_listTile[i][j]->Nodetype == NODE_TYPE::START)
			{
				HBRUSH hbr = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
				HBRUSH hbrOld = (HBRUSH)SelectObject(hdc, hbr);

				Rectangle(hdc, m_listTile[i][j]->Pos.x, m_listTile[i][j]->Pos.y,
					m_listTile[i][j]->Pos.x + TILE_CWIDTH, m_listTile[i][j]->Pos.y + TILE_CHEIGHT);

				hbr = (HBRUSH)::SelectObject(hdc, hbrOld);
				DeleteObject(hbr);
			}
			else if (m_listTile[i][j]->Nodetype == NODE_TYPE::END)
			{
				HBRUSH hbr = (HBRUSH)CreateSolidBrush(RGB(0, 0, 255));
				HBRUSH hbrOld = (HBRUSH)SelectObject(hdc, hbr);

				Rectangle(hdc, m_listTile[i][j]->Pos.x, m_listTile[i][j]->Pos.y,
					m_listTile[i][j]->Pos.x + TILE_CWIDTH, m_listTile[i][j]->Pos.y + TILE_CHEIGHT);

				hbr = (HBRUSH)::SelectObject(hdc, hbrOld);
				DeleteObject(hbr);
			}
			else if (m_listTile[i][j]->Nodetype == NODE_TYPE::OBSTACLE)
			{
				HBRUSH hbr = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
				HBRUSH hbrOld = (HBRUSH)SelectObject(hdc, hbr);

				Rectangle(hdc, m_listTile[i][j]->Pos.x, m_listTile[i][j]->Pos.y,
					m_listTile[i][j]->Pos.x + TILE_CWIDTH, m_listTile[i][j]->Pos.y + TILE_CHEIGHT);

				hbr = (HBRUSH)::SelectObject(hdc, hbrOld);
				DeleteObject(hbr);
			}
			else if (m_listTile[i][j]->Nodetype == NODE_TYPE::NORMAL)
			{
				HBRUSH hbr = (HBRUSH)CreateSolidBrush(RGB(255, 255, 255));
				HBRUSH hbrOld = (HBRUSH)SelectObject(hdc, hbr);

				Rectangle(hdc, m_listTile[i][j]->Pos.x, m_listTile[i][j]->Pos.y,
					m_listTile[i][j]->Pos.x + TILE_CWIDTH, m_listTile[i][j]->Pos.y + TILE_CHEIGHT);

				hbr = (HBRUSH)::SelectObject(hdc, hbrOld);
				DeleteObject(hbr);
			}
			else if (m_listTile[i][j]->Nodetype == NODE_TYPE::OPEN)
			{
				HBRUSH hbr = (HBRUSH)CreateSolidBrush(RGB(0, 255, 0));
				HBRUSH hbrOld = (HBRUSH)SelectObject(hdc, hbr);

				Rectangle(hdc, m_listTile[i][j]->Pos.x, m_listTile[i][j]->Pos.y,
					m_listTile[i][j]->Pos.x + TILE_CWIDTH, m_listTile[i][j]->Pos.y + TILE_CHEIGHT);

				hbr = (HBRUSH)::SelectObject(hdc, hbrOld);
				DeleteObject(hbr);
			}
			else if (m_listTile[i][j]->Nodetype == NODE_TYPE::CLOSE)
			{
				HBRUSH hbr = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
				HBRUSH hbrOld = (HBRUSH)SelectObject(hdc, hbr);

				Rectangle(hdc, m_listTile[i][j]->Pos.x, m_listTile[i][j]->Pos.y,
					m_listTile[i][j]->Pos.x + TILE_CWIDTH, m_listTile[i][j]->Pos.y + TILE_CHEIGHT);

				hbr = (HBRUSH)::SelectObject(hdc, hbrOld);
				DeleteObject(hbr);
			}

			TCHAR chG[120];
			_itow(m_listTile[i][j]->G, chG, 10);
			TCHAR chH[120];
			_itow(m_listTile[i][j]->H, chH, 10);
			TCHAR chF[120];
			_itow(m_listTile[i][j]->F, chF, 10);

			SetBkMode(hdc, TRANSPARENT);

			SetTextAlign(hdc, TA_LEFT);
			TextOut(hdc, m_listTile[i][j]->Pos.x + 2, m_listTile[i][j]->Pos.y, chG, _tcslen(chG));

			SetTextAlign(hdc, TA_RIGHT);
			TextOut(hdc, m_listTile[i][j]->Pos.x + (TILE_CWIDTH) - 2, m_listTile[i][j]->Pos.y, chH, _tcslen(chH));

			SetTextAlign(hdc, TA_BOTTOM|TA_CENTER);
			TextOut(hdc, m_listTile[i][j]->Pos.x + (TILE_CWIDTH * 0.5), m_listTile[i][j]->Pos.y+TILE_CHEIGHT, chF, _tcslen(chF));

		}
	}
}

void CNodeMgr::Release()
{
	delete[] m_listTile;
}

//
//bool CNodeMgr::Check_isSetStartEnd()
//{
//	POINT pt;
//	GetCursorPos(&pt);
//	ScreenToClient(CCore::GetInst()->Get_Hwnd(), &pt);
//
//	int row = pt.y / TILE_COL;
//	int col = pt.x / TILE_ROW;
//
//	m_listTile[row][col]->Nodetype = NODE_TYPE::START;
//
//}
