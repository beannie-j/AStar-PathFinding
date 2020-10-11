#include "Node.h"
#include "Map.h"

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
void Node::CalculateHCost(Node endNode, int& hCost)
{
	hCost = GetDistance(*this, endNode);
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

std::vector<Node> Node::GetNeighbours()
{
	// clear previous neighbours
	std::vector<Node> neighbours;

	// looping through -1 to 1 x and y, skip 0 cos that's the node itself.
	for (int x = -1; x <= 1; x++)
	{
		for (int y = -1; y <= 1; y++)
		{
			if (x == 0 && y == 0) continue;

			int checkX = m_PosX + x;
			int checkY = m_PosY + y;
			
			// make sure to checkX and checkY doesnt go out of grid bounds
			if (checkX >= 0 && checkX < Map::m_GridWidth 
				&& checkY >= 0 && checkY < Map::m_GridHeight) {
				neighbours.emplace_back(Node(checkX, checkY));
			}
		}
	}
	return neighbours;
}