#pragma once

#include <array>
#include <stack>

#include "Node.h"

class Maze
{
private:
	std::array<std::pair<int, int>, 4> dirs = { { {1,0}, {-1,0}, {0,1}, {0,-1} } };
	std::stack<Node> visited;

public:
	void Create(int x, int y);
	bool Contains(std::stack<Node> vec, Node node);
};

