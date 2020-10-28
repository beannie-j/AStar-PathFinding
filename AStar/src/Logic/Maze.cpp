#include "Maze.h"
#include "Map.h"

#include <vector>

#include <stdlib.h>

void Maze::Create(int x, int y)
{
	auto& map = Map::Get();
	Map::NodeGrid& grid = map.GetGrid();
	int VisitedCellsNum = 0;

#if 0
	Node node = map.GetNode(x, y);
	std::vector<Node> neighbours = node.GetNeighbours();

	if (!neighbours.empty())
	{
		int NextRandomCell = rand() % neighbours.size();

		if (!Contains(visited, neighbours.at(NextRandomCell)))
		{
			visited.push(node);
		}
	}
	
	else 
	{
		// pick random neighbour.
	}
#endif
}

bool Maze::Contains(std::stack<Node> stack, Node node)
{
	while (!stack.empty() && stack.top() != node)
	{
		stack.pop();
	}

	if (!stack.empty())
	{
		return true;
	}

	return false;
}

