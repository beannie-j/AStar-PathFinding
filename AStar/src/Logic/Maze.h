#pragma once

#include <array>
#include <optional>
#include <stack>
#include <vector>

#include "Node.h"

class Maze
{
private:
	std::stack<Node> m_PathStack;
	std::vector<Node> m_Visited;
	int m_NumVisitedCells = 1;

public:
	void Create(int x, int y);
	std::vector<Node> GetNeighboursNonDiagonal(Node node);
	bool Contains(std::vector<Node> vec, Node node);
};

