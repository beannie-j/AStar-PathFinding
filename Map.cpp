#include "Map.h"
#include <iostream>

void Map::Init()
{
	// Create nodes
	for (int x = 0; x < m_GridWidth; x++)
	{
		for (int y = 0; y < m_GridHeight; y++)
		{
			grid[x][y] = Node(x, y);
		}
	}
}
