#include "Map.h"
#include <iostream>

static Map* s_Instance = nullptr;

void Map::Init()
{
	// Create nodes
	for (int x = 0; x < GridWidth; x++)
	{
		for (int y = 0; y < GridHeight; y++)
		{
			Add(Node(x, y, false));
		}
	}
}

void Map::Draw()
{
	for (int y = 0; y < GridHeight; y++)
	{
		for (int x = 0; x < GridWidth; x++)
		{
			if (grid[x + y * GridWidth].mark > 0)
			{
				std::cout << grid[x + y * GridWidth].mark << " ";
			}
			else std::cout << ". ";
		}
		std::cout << "\n";
	}
}

void Map::Add(Node& node)
{
	int x = node.m_PosX;
	int y = node.m_PosY;
	grid[x + y * GridWidth] = node;
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

Map::Map()
{
	s_Instance = this;
}

Map::~Map()
{
	//delete s_Instance;
}
