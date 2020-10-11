#pragma once
#include "Node.h"
class Map
{
public:
	static constexpr int m_GridWidth = 30;
	static constexpr int m_GridHeight = 20;

	Node grid[m_GridWidth][m_GridHeight];
	Node* startNode = nullptr;
	Node* endNode = nullptr;

	void Init();

	Map() = default;
};

