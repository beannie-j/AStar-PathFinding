#include "Map.h"
#include <iostream>

static Map* s_Instance = nullptr;

int Map::Size()
{
	return GridWidth * GridHeight;
}

void Map::Init()
{
	// Create nodes
	for (int x = 0; x < GridWidth; x++)
	{
		for (int y = 0; y < GridHeight; y++)
		{
			Add(Node(x, y, false, false));
		}
	}
}

void Map::Draw()
{
	for (int y = 0; y < GridHeight; y++)
	{
		for (int x = 0; x < GridWidth; x++)
		{
			if (grid[x + y * GridWidth].m_Mark > 0)
			{
				std::cout << grid[x + y * GridWidth].m_Mark << " ";
			}
			else std::cout << ". ";
		}
		std::cout << "\n";
	}
}

void Map::Add(const Node& node)
{
	int x = node.m_PosX;
	int y = node.m_PosY;
	if (x < 0 || x >= GridWidth || y < 0 || y >= GridHeight)
	{
		std::cout << "Out of bounds!\n";
	}
	else
	{
		grid[x + y * GridWidth] = node;
	}
}

Map& Map::Get()
{
	return *s_Instance;
}

Map::NodeGrid& Map::GetGrid()
{
	return grid;
}

Node& Map::GetNode(int x, int y)
{
	return grid[x + y * GridWidth];
}

std::vector<Node> Map::GetObstacles()
{
	std::vector<Node> obstacles;

	for (int y = 0; y < GridHeight; y++)
	{
		for (int x = 0; x < GridWidth; x++)
		{
			if (grid[x + y * GridWidth].m_IsObstacle)
			{
				obstacles.push_back(GetNode(x, y));
			}
		}
	}
	return obstacles;
}

std::vector<Node> Map::GetPathNodes()
{
	std::vector<Node> PathNodes;

	for (int y = 0; y < GridHeight; y++)
	{
		for (int x = 0; x < GridWidth; x++)
		{
			if (grid[x + y * GridWidth].m_Mark == 'P')
			{
				PathNodes.push_back(GetNode(x, y));
			}
		}
	}
	return PathNodes;
}

std::vector<Node> Map::GetVisitedNodes()
{
	std::vector<Node> VisitedNodes;

	for (int y = 0; y < GridHeight; y++)
	{
		for (int x = 0; x < GridWidth; x++)
		{
			if (grid[x + y * GridWidth].m_Mark == 'V')
			{
				VisitedNodes.push_back(GetNode(x, y));
			}
		}
	}
	return VisitedNodes;
}

std::vector<Node> Map::GetWalls()
{
	std::vector<Node> walls;

	for (int y = 0; y < GridHeight; y++)
	{
		for (int x = 0; x < GridWidth; x++)
		{
			if (grid[x + y * GridWidth].m_Mark == 'W')
			{
				walls.push_back(GetNode(x, y));
			}
		}
	}
	return walls;
}

void Map::ResetObstacles()
{
	for (int y = 0; y < GridHeight; y++)
	{
		for (int x = 0; x < GridWidth; x++)
		{
			if (grid[x + y * GridWidth].m_IsObstacle)
			{
				grid[x + y * GridWidth].m_IsObstacle = false;
			}
		}
	}
}

void Map::ResetPath()
{
	for (int y = 0; y < GridHeight; y++)
	{
		for (int x = 0; x < GridWidth; x++)
		{
			if (grid[x + y * GridWidth].m_Mark == 'P' || grid[x + y * GridWidth].m_Mark == 'E' || grid[x + y * GridWidth].m_Mark == 'V' || grid[x + y * GridWidth].m_Mark == 'X')
			{
				grid[x + y * GridWidth].m_Mark = '.';
			}
		}
	}
}

Map::Map()
{
	s_Instance = this;
}

Map::~Map()
{
	//delete s_Instance;
}
