#include "Maze.h"
#include "Map.h"

#include <stack>
#include <stdlib.h>
#include <algorithm>
#include <iostream>

void Maze::BeginMaze(const Node& startNode)
{	// empty 
	auto& map = Map::Get();
	map.ResetPath();

	m_Visited.clear();
	while (!m_PathStack.empty()) { m_PathStack.pop(); }

	m_StartNode = startNode;
	m_Visited.push_back(m_StartNode);
}

bool Maze::NextStep()
{
	auto& map = Map::Get();

	auto& pathStack = m_PathStack;
	auto& visited = m_Visited;

	Node node = visited.back();
	
	std::vector<Node> neighbours = GetNeighboursNonDiagonal(node);

	// check for possible neighbours it can visit to and picks next node to go to.
	if (!neighbours.empty())
	{
		int randIdx = rand() % neighbours.size();
		Node nextNode = neighbours[randIdx];
		m_NumVisitedCells += 1;
		pathStack.push(node);
		visited.push_back(nextNode);
	}
	else // neighbour stack is empty, no where to go to, start backtracking.
	{
		if (pathStack.size() <= 0) return true;
		node = pathStack.top();
		visited.push_back(node);
		pathStack.pop();
	}
	
	if (m_NumVisitedCells >= map.Size())
	{
		pathStack.push(visited.back());
		m_MazeGenerated = true;
		return true;
	}
	return false;
}

void Maze::EndMazeGenerating()
{
	auto& map = Map::Get();
	auto& pathStack = m_PathStack;

	while (!pathStack.empty())
	{
		Node temp = pathStack.top();
		temp.m_Mark = 'M';
		//temp.Print();
		map.Add(temp);
		m_PathVector.push_back(temp);
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
		{  0, -1 }
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

				switch (i)
				{
				case 0:
					candidate.dir = 0;
					break;

				case 1:
					candidate.dir = 1;
					break;
				
				case 2:
					candidate.dir = 2;
					break;

				case 3:
					candidate.dir = 3;
					break;
				}

				if (!Contains(m_Visited, candidate) && !candidate.m_IsObstacle)
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
