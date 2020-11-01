#include "Maze.h"
#include "Map.h"

#include <stack>
#include <stdlib.h>
#include <algorithm>
#include <iostream>

void Maze::Create(int x, int y) // start at x, y
{
	auto& map = Map::Get();
	Map::NodeGrid& grid = map.GetGrid();

	auto& pathStack = m_PathStack;
	auto& visited = m_Visited;

	Node node = map.GetNode(x, y);

	pathStack.push(node);
	visited.push_back(node);

	while (m_NumVisitedCells < map.Size())
	{
		std::vector<Node> neighbours = GetNeighboursNonDiagonal(node);

		if (!neighbours.empty())
		{
			int randIdx = rand() % neighbours.size();
			Node nextNode = neighbours[randIdx];

			pathStack.push(nextNode);
			visited.push_back(nextNode);

			m_NumVisitedCells += 1;
			node = nextNode;
		}
		else // neighbour stack is empty, no where to go to, start backtracking.
		{
			node = pathStack.top();
			pathStack.pop();
		}
	}

	
	while (!pathStack.empty())
	{
		Node temp = pathStack.top();
		temp.Print();
		temp.m_Mark = 'M';
		map.Add(temp);
		pathStack.pop();
	}

	map.Draw();

}

// only gets non diagonal neighbours and unvisited ones
std::vector<Node> Maze::GetNeighboursNonDiagonal(Node node)
{
	std::vector<Node> neighboursNonDiagonal;

	auto& map = Map::Get();
	Map::NodeGrid& grid = map.GetGrid();

	struct Direction
	{
		int X, Y;
	};

	constexpr Direction directions[4] =
	{
		// Non-diagonals
		{ -1,  0 },
		{  0,  1 },
		{  1,  0 },
		{  0, -1 },
	};

	for (int i = 0; i < 4; i++)
	{
		int nodeX = node.m_PosX;
		int nodeY = node.m_PosY;

		int checkX = nodeX + directions[i].X;
		int checkY = nodeY + directions[i].Y;

		if (checkX >= 0 && checkX < Map::GridWidth
			&& checkY >= 0 && checkY < Map::GridHeight)
			{
				Node& candidate = grid[checkX + checkY * Map::GridWidth];
				if (!candidate.m_IsObstacle && !Contains(m_Visited, candidate))
					neighboursNonDiagonal.push_back(candidate);
			}
	}
	return neighboursNonDiagonal;
}

bool Maze::Contains(std::vector<Node> vec, Node node)
{
	for (const Node& elem : vec)
	{
		if (elem == node)
		{
			return true;
		}
	}
	return false;
}
