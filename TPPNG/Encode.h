#pragma once
#include "stdafx.h"
#include <cmath> 
using namespace std;

struct Point
{
	int x;
	int y;
	Point(int _x, int _y)
	{
		x = _x;
		y = _y;
	}
	Point()
	{
		x = 0;
		y = 0;
	}
};

struct Node
{
	Point pos;
	int data;
	Node(Point _pos, int _data)
	{
		pos = _pos;
		data = _data;
	}
	Node()
	{
		data = 0;
	}
};

class QuadTree
{
	Point topLeft;
	Point botRight;
	Node *n;
	QuadTree *topLeftTree;
	QuadTree *topRightTree;
	QuadTree *botLeftTree;
	QuadTree *botRightTree;

public:
	QuadTree();
	QuadTree(Point topL, Point botR);
	void insertNode(Node*);
	bool inSquare(Point);
};



