#pragma once

class CNodeMgr
{
	SINGLETONE(CNodeMgr);

public:
	void Init();
	void Update();
	void LateUpdate();
	void Render(HDC hdc);
	void Release();

public:

	void Set_SurrNode(Node* N);
	void Set_GHFandPush_PQ(int row, int col, DIR_TYPE type);

	int Get_H(int row, int col);



private:

	bool m_isReach;

	int m_iEndNode_row;
	int m_iEndNode_col;

	Node* m_listTile[TILE_ROW][TILE_COL];

	Node *m_StartNode;
	Node *m_EndNode;

	priority_queue <Node*, vector<Node*>, cmp> m_PQ;
};

