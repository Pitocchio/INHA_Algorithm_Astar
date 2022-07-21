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

	//bool Check_isSetStartEnd();


private:

	Node* m_listTile[TILE_ROW][TILE_COL];
	priority_queue <Node*, vector<Node*>, cmp> m_PQ;
};

