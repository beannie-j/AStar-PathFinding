#pragma once
#include "Node.h"
class Map
{
public:
	static constexpr int m_GridWidth = 50;
	static constexpr int m_GridHeight = 50;

	Node grid[m_GridWidth][m_GridHeight];
	Node* startNode = nullptr;
	Node* endNode = nullptr;

	void Init();

	Map() = default;
};

