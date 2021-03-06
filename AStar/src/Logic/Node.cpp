#include "Node.h"
#include "Map.h"
#include <iostream>

void Node::CalculateFCost(int& fCost)
{
	fCost = m_GCost + m_HCost;
}

// G Cost - distance from starting node
void Node::CalculateGCost(Node startNode, int& gCost)
{
	gCost = GetDistance(*this, startNode);
}
// H cost (Heuristic cost) - opposite of G cost, how far is this node from the destination node
int Node::CalculateHCost(Node endNode)
{
	return GetDistance(*this, endNode);
}

int Node::GetDistance(Node nodeA, Node nodeB)
{
	int dstX = std::abs(nodeA.m_PosX - nodeB.m_PosX);
	int dstY = std::abs(nodeA.m_PosY - nodeB.m_PosY);
	// nodeA is at a lower location than nodeB 14y + 10 (x-y)
	if (dstX > dstY)
	{
		return 14 * dstY + 10 * (dstX - dstY);
	}

	return 14 * dstX + 10 * (dstY - dstX);
}

std::array<std::optional<Node>, 8> Node::GetNeighbours()
{
	std::array<std::optional<Node>, 8> neighbours;

	auto& map = Map::Get();
	Map::NodeGrid& grid = map.GetGrid();

	// instead of only adding valid nodes, 

	struct Direction
	{
		int X, Y;
	};

	constexpr Direction directions[8] =
	{
		// Non-diagonals
		{ -1,  0 },
		{  0,  1 },
		{  1,  0 },
		{  0, -1 },
		
		// Diagonals
		{ -1,  1 },
		{  1,  1 },
		{  1, -1 },
		{ -1, -1 }
		
	};

	for (int i = 0; i < 8; i++)
	{
		int checkX = m_PosX + directions[i].X;
		int checkY = m_PosY + directions[i].Y;

		if (checkX >= 0 && checkX < Map::GridWidth
			&& checkY >= 0 && checkY < Map::GridHeight)
		{
			Node& candidate = grid[checkX + checkY * Map::GridWidth];
			if (!candidate.m_IsObstacle)
				neighbours[i] = candidate;
		}
	}

#if OLD
	// looping through -1 to 1 x and y, skip 0 cos that's the node itself.
	for (int x = -1; x <= 1; x++)
	{
		for (int y = -1; y <= 1; y++)
		{
			if (x == 0 && y == 0) continue;

			if (m_IsObstacle)
			{
				continue;
			}

			int checkX = m_PosX + x;
			int checkY = m_PosY + y;
			
			// make sure to checkX and checkY doesnt go out of grid bounds
			if (checkX >= 0 && checkX < Map::GridWidth 
				&& checkY >= 0 && checkY < Map::GridHeight) {
				neighbours.push_back(grid[checkX + checkY * Map::GridWidth]);
			}
		}
	}
#endif
	return neighbours;
}

void Node::Print() const
{
	std::cout << " [" << m_PosX << " , " << m_PosY << "] FCost: " << m_FCost << " HCost: " << m_HCost << " GCost: " << m_GCost << " Obstacle: " << m_IsObstacle;
	if (m_Parent != nullptr)
	{
		std::cout << " [Parent] " << m_Parent->m_PosX << " , " << m_Parent->m_PosY << '\n';
	}

	else 
		std::cout << '\n';
}

bool operator==(const Node& lhs, const Node& rhs)
{
	if (lhs.m_PosX == rhs.m_PosX && lhs.m_PosY == rhs.m_PosY)
	{
		return true;
	}

	return false;
}

bool operator!=(const Node& lhs, const Node& rhs)
{
	return !(lhs == rhs);
}
