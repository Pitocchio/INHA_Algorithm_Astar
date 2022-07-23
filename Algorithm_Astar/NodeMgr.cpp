#include "stdafx.h"
#include "NodeMgr.h"

CNodeMgr* CNodeMgr::m_pInst = nullptr;

void CNodeMgr::Init()
{
	m_bReach = false;
	m_bRouteSet = false;

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

	// 마우스 입력 대신
	{
		
		// 알고리즘 구현 후, 마우스 입력으로 바꾸자

		// START
		m_listTile[4][4]->Nodetype = NODE_TYPE::START;
		m_StartNode = m_listTile[4][4];
		m_PQ.push(m_listTile[4][4]);

		// END
		m_listTile[17][19]->Nodetype = NODE_TYPE::END;
		m_EndNode = m_listTile[17][19];
		m_iEndNode_row = 17;
		m_iEndNode_col = 19;

		// OBSTACLE
		m_listTile[5][7]->Nodetype = NODE_TYPE::OBSTACLE;
		m_listTile[5][8]->Nodetype = NODE_TYPE::OBSTACLE;
		m_listTile[6][8]->Nodetype = NODE_TYPE::OBSTACLE;
		m_listTile[7][8]->Nodetype = NODE_TYPE::OBSTACLE;
		m_listTile[7][7]->Nodetype = NODE_TYPE::OBSTACLE;
		m_listTile[7][6]->Nodetype = NODE_TYPE::OBSTACLE;
		m_listTile[7][5]->Nodetype = NODE_TYPE::OBSTACLE;

		m_listTile[11][13]->Nodetype = NODE_TYPE::OBSTACLE;
		m_listTile[11][12]->Nodetype = NODE_TYPE::OBSTACLE;
		m_listTile[11][11]->Nodetype = NODE_TYPE::OBSTACLE;

		m_listTile[11][10]->Nodetype = NODE_TYPE::OBSTACLE;
		m_listTile[11][9]->Nodetype = NODE_TYPE::OBSTACLE;
		m_listTile[11][8]->Nodetype = NODE_TYPE::OBSTACLE;
		m_listTile[11][7]->Nodetype = NODE_TYPE::OBSTACLE;

		m_listTile[11][6]->Nodetype = NODE_TYPE::OBSTACLE;
		m_listTile[11][5]->Nodetype = NODE_TYPE::OBSTACLE;


		m_listTile[10][4]->Nodetype = NODE_TYPE::OBSTACLE;
		m_listTile[10][7]->Nodetype = NODE_TYPE::OBSTACLE;
		m_listTile[14][11]->Nodetype = NODE_TYPE::OBSTACLE;
		m_listTile[14][12]->Nodetype = NODE_TYPE::OBSTACLE;
		m_listTile[14][13]->Nodetype = NODE_TYPE::OBSTACLE;
		m_listTile[15][14]->Nodetype = NODE_TYPE::OBSTACLE;
		m_listTile[14][6]->Nodetype = NODE_TYPE::OBSTACLE;
		m_listTile[13][7]->Nodetype = NODE_TYPE::OBSTACLE;
		m_listTile[12][8]->Nodetype = NODE_TYPE::OBSTACLE;
		m_listTile[11][9]->Nodetype = NODE_TYPE::OBSTACLE;


	
		m_listTile[17][16]->Nodetype = NODE_TYPE::OBSTACLE;
		m_listTile[16][16]->Nodetype = NODE_TYPE::OBSTACLE;
		m_listTile[15][16]->Nodetype = NODE_TYPE::OBSTACLE;
		m_listTile[14][16]->Nodetype = NODE_TYPE::OBSTACLE;
		m_listTile[13][16]->Nodetype = NODE_TYPE::OBSTACLE;
		m_listTile[12][16]->Nodetype = NODE_TYPE::OBSTACLE;
		m_listTile[11][16]->Nodetype = NODE_TYPE::OBSTACLE;

		m_listTile[17][11]->Nodetype = NODE_TYPE::OBSTACLE;
		m_listTile[17][12]->Nodetype = NODE_TYPE::OBSTACLE;
		m_listTile[17][13]->Nodetype = NODE_TYPE::OBSTACLE;
		m_listTile[17][14]->Nodetype = NODE_TYPE::OBSTACLE;
		m_listTile[17][15]->Nodetype = NODE_TYPE::OBSTACLE;

	}
}



void CNodeMgr::Update()
{
	if(!m_PQ.empty() && !m_bReach)
	{
		/*int i = 0;
		while (!m_PQ.empty())
		{
			printf("[%d] G = %d\tH = %d\tF = %d\n\n",
				i++, m_PQ.top()->G, m_PQ.top()->H, m_PQ.top()->F);

			m_PQ.pop();
		}

		int t = 1;*/

		if (m_PQ.top()->Nodetype == NODE_TYPE::END)
		{
			cout << "도착했습니다~\n";
			m_bReach = true;
			return;
		}

		// N을 CLOSE 처리
		if (m_PQ.top()->Nodetype != NODE_TYPE::START)
		{
			m_PQ.top()->Nodetype = NODE_TYPE::CLOSE;
		}

		// 함수 들어가서 우선 pop
		// 우선 순위 큐 탑 주변 8개 노드를 찾아 
		// G, H, F와 NODETYPE을 세팅, 그리고 그 노드들을 우선 순위 큐에 넣어준다
		Set_SurrNode(m_PQ.top());

		int k = 999;
	}
}

void CNodeMgr::Set_SurrNode(Node* N)
{
	m_PQ.pop();

	for (int i = 0; i < TILE_ROW; ++i)
	{
		for (int j = 0; j < TILE_COL; ++j)
		{
			if (m_listTile[i][j]->Num == N->Num)
			{
				Set_GHFandPush_PQ(N, i - 1, j, DIR_TYPE::PLUS);
				Set_GHFandPush_PQ(N, i + 1, j, DIR_TYPE::PLUS);
				Set_GHFandPush_PQ(N, i, j + 1, DIR_TYPE::PLUS);
				Set_GHFandPush_PQ(N, i, j - 1, DIR_TYPE::PLUS);
								 
				Set_GHFandPush_PQ(N, i - 1, j + 1, DIR_TYPE::MUL);
				Set_GHFandPush_PQ(N, i + 1, j + 1, DIR_TYPE::MUL);
				Set_GHFandPush_PQ(N, i - 1, j - 1, DIR_TYPE::MUL);
				Set_GHFandPush_PQ(N, i + 1, j - 1, DIR_TYPE::MUL);
			}
		}
	}
}


void CNodeMgr::Set_GHFandPush_PQ(Node* N, int row, int col, DIR_TYPE type)
{
	if ((row - 1) < 0 || (col - 1) < 0 || (row + 1) > 20 || (col + 1) > 20)
		return;

	// 1차 필터링 (시작노드, 닫힌 노드, 장애물노드는 데이터를 갱신하지 않는다) // edit
	if (m_listTile[row][col]->Nodetype == NODE_TYPE::START
		|| m_listTile[row][col]->Nodetype == NODE_TYPE::CLOSE
		|| m_listTile[row][col]->Nodetype == NODE_TYPE::OBSTACLE) // edit
		return;

	// 2차 필터링 (갱신전 F값과 갱신후 F값을 비교하여 갱신후 F값이 더 작다면 갱신 진행) // edit

	int preG = m_listTile[row][col]->G; // 이전 G값
	int preH = m_listTile[row][col]->H; // 이전 H값
	int preF = m_listTile[row][col]->F; // 이전 F값

	int curG = Get_G(N, row, col, type);
	int curH = Get_H(row, col);
	int curF = curG + curH;

	if (preF > curF) // 2차 필터링 걸린다면 
	{
		list <Node*> templist;
		bool bSet = false;
		// 삭제 후 다시 푸시
		while (!m_PQ.empty())
		{
			if (m_PQ.top()->Num == m_listTile[row][col]->Num)
			{
		
				m_listTile[row][col]->G = curG;
				m_listTile[row][col]->H = curH;
				m_listTile[row][col]->F = curF;

				m_PQ.pop();
				m_PQ.push(m_listTile[row][col]);

				while (!templist.empty())
				{
					m_PQ.push(templist.front());
					templist.pop_front();
					bSet = true;
				}
			}

			if (bSet)
				break;
			templist.push_back(m_PQ.top());
			m_PQ.pop();
		}
		
	}
	else if ((preF < curF) && (m_listTile[row][col]->F == 0)) // 2차 필터링 안걸리고, 노드가 비어있다면
	{
		m_listTile[row][col]->G = curG;
		m_listTile[row][col]->H = curH;
		m_listTile[row][col]->F = curF;

		if(m_listTile[row][col]->Nodetype != NODE_TYPE::END)
			m_listTile[row][col]->Nodetype = NODE_TYPE::OPEN;

		m_PQ.push(m_listTile[row][col]);
	}
	else if ((preF < curF) && (m_listTile[row][col]->F != 0)) // 2차 필터링 안걸리고, 노드가 비어있지 않다면
	{
		m_listTile[row][col]->G = preG;
		m_listTile[row][col]->H = preH;
		m_listTile[row][col]->F = preF;


	}
}

int CNodeMgr::Get_H(int row, int col)
{
	int iNumLine;
	int iNumCross;
	int a = abs(row - m_iEndNode_row);
	int b = abs(col - m_iEndNode_col);
	
	if (a > b)
	{
		iNumLine = a - b;
		iNumCross = b;
	}
	else
	{
		iNumLine = b - a;
		iNumCross = a;
	}

	return (iNumLine * 10) + (iNumCross * 14);
}

int CNodeMgr::Get_G(Node* N, int row, int col, DIR_TYPE type)
{
	int tempG = 0;;

	if (type == DIR_TYPE::PLUS)
	{
		tempG = N->G + 10;
	}
	else if (type == DIR_TYPE::MUL)
	{
		tempG = N->G + 14;
	}
	return tempG;
}

void CNodeMgr::Render(HDC hdc)
{
	for (int i = 0; i < TILE_ROW; ++i)
	{
		for (int j = 0; j < TILE_COL; ++j)
		{
			if (m_listTile[i][j]->Nodetype == NODE_TYPE::START)
			{
				HBRUSH hbr = (HBRUSH)CreateSolidBrush(RGB(255, 255, 0));
				HBRUSH hbrOld = (HBRUSH)SelectObject(hdc, hbr);

				Rectangle(hdc, m_listTile[i][j]->Pos.x, m_listTile[i][j]->Pos.y,
					m_listTile[i][j]->Pos.x + TILE_CWIDTH, m_listTile[i][j]->Pos.y + TILE_CHEIGHT);

				hbr = (HBRUSH)::SelectObject(hdc, hbrOld);
				DeleteObject(hbr);

				SetBkMode(hdc, TRANSPARENT);
				SetTextAlign(hdc, TA_CENTER);
				TextOut(hdc, int(m_listTile[i][j]->Pos.x + (TILE_CWIDTH * 0.5)), int(m_listTile[i][j]->Pos.y + (TILE_CHEIGHT * (0.35))),
					_T("START"), _tcslen(_T("START")));

			}
			else if (m_listTile[i][j]->Nodetype == NODE_TYPE::END)
			{
				HBRUSH hbr = (HBRUSH)CreateSolidBrush(RGB(0, 0, 255));
				HBRUSH hbrOld = (HBRUSH)SelectObject(hdc, hbr);

				Rectangle(hdc, m_listTile[i][j]->Pos.x, m_listTile[i][j]->Pos.y,
					m_listTile[i][j]->Pos.x + TILE_CWIDTH, m_listTile[i][j]->Pos.y + TILE_CHEIGHT);

				hbr = (HBRUSH)::SelectObject(hdc, hbrOld);
				DeleteObject(hbr);

				SetBkMode(hdc, TRANSPARENT);
				SetTextAlign(hdc, TA_CENTER);
				TextOut(hdc, int(m_listTile[i][j]->Pos.x + (TILE_CWIDTH * 0.5)), int(m_listTile[i][j]->Pos.y + (TILE_CHEIGHT * (0.35))),
					_T("END"), _tcslen(_T("END")));
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
			else if (m_listTile[i][j]->Nodetype == NODE_TYPE::ROUTE)
			{
				HBRUSH hbr = (HBRUSH)CreateSolidBrush(RGB(100, 100, 100));
				HBRUSH hbrOld = (HBRUSH)SelectObject(hdc, hbr);

				Rectangle(hdc, m_listTile[i][j]->Pos.x, m_listTile[i][j]->Pos.y,
					m_listTile[i][j]->Pos.x + TILE_CWIDTH, m_listTile[i][j]->Pos.y + TILE_CHEIGHT);

				hbr = (HBRUSH)::SelectObject(hdc, hbrOld);
				DeleteObject(hbr);
			}

			if (m_listTile[i][j]->Nodetype == NODE_TYPE::NORMAL)
				continue;
			
			TCHAR chG[120];
			_itow(m_listTile[i][j]->G, chG, 10);
			TCHAR chH[120];
			_itow(m_listTile[i][j]->H, chH, 10);
			TCHAR chF[120];
			_itow(m_listTile[i][j]->F, chF, 10);

			SetBkMode(hdc, TRANSPARENT);

			SetTextAlign(hdc, TA_LEFT);
			TextOut(hdc, int(m_listTile[i][j]->Pos.x + 2), int(m_listTile[i][j]->Pos.y), chG, _tcslen(chG));

			SetTextAlign(hdc, TA_RIGHT);
			TextOut(hdc, int(m_listTile[i][j]->Pos.x + (TILE_CWIDTH) - 2), int(m_listTile[i][j]->Pos.y), chH, _tcslen(chH));

			SetTextAlign(hdc, TA_BOTTOM|TA_CENTER);
			TextOut(hdc, int(m_listTile[i][j]->Pos.x + (TILE_CWIDTH * 0.5)), int(m_listTile[i][j]->Pos.y+TILE_CHEIGHT), chF, _tcslen(chF));

			
		}
	}
}

void CNodeMgr::Release()
{
	for (int i = 0; i < TILE_ROW; ++i)
	{
		for (int j = 0; j < TILE_COL; ++j)
		{
			delete m_listTile[i][j];
		}
	}
}
