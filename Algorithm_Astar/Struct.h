#pragma once
#include <windef.h>
#include "Enum.h"

typedef struct Node
{
	int Num = 0;

	NODE_TYPE Nodetype = NODE_TYPE::NORMAL;

	int G = 0;
	int H = 0;
	int F = 0;

	POINT Pos = { 0,0 };


}Node;


typedef struct cmp
{
	//오름차순 정렬 (return 값이 true라면 swap을 진행한다)
	bool operator() (Node* a, Node* b)
	{
		if (a->F != b->F)
			return a->F > b->F;
		else if (a->F == b->F)
			return  a->H > b->H;
	}

}cmp;

