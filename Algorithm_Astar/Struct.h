#pragma once
#include <windef.h>
#include <Enum.h>

typedef struct Node
{
	POINT Pos = { 0,0 };

	int G = 0;
	int H = 0;
	int F = 0;
	int Num = 0;

	NODE_TYPE Nodetype = NODE_TYPE::NORMAL;
	
}Node;

typedef struct cmp
{
	bool operator() (Node* a, Node* b) 
	{
		if ((*a).F == (*b).F)
			return (*a).H > (*b).H;
		else
			return (*a).F > (*b).F;
	}

}cmp;