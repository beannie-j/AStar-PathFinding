#pragma once
#include "Node.h"
class Map
{
public:
	static constexpr int m_GridWidth = 100;
	static constexpr int m_GridHeight = 100;

	Node grid[m_GridWidth][m_GridHeight];
	Node* startNode = nullptr;
	Node* endNode = nullptr;

	void Init();
};

