#pragma once

class CNodeMgr
{
	SINGLETONE(CNodeMgr);

public: // LifeCycle
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

public: // Method
	void Set_SurrNode(Node* N);
	void Set_GHFandPush_PQ(Node* N, int row, int col, DIR_TYPE type);
	int Get_H(int row, int col);
	int Get_G(Node* N, int row, int col, DIR_TYPE type);

private: // Variables
	bool m_bReach;
	bool m_bRouteSet;
	int m_iEndNode_row;
	int m_iEndNode_col;
	Node* m_listTile[TILE_ROW][TILE_COL];
	Node *m_StartNode;
	Node *m_EndNode;
	priority_queue <Node*, vector<Node*>, cmp> m_PQ; // Open priority_queue

};
