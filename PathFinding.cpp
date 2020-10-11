#include "PathFinding.h"

#include <vector>
#include <unordered_set>
#include <cmath>

void PathFinding::FindPath(Node startNode, Node targetNode)
{
	Node currentNode = startNode;
	std::vector<Node> neighbours = currentNode.GetNeighbours();
	std::vector<Node> toExplore;

	for (Node node : neighbours)
	{
		// calculate gCost and hCost
		node.CalculateGCost();
		node.CalculateHCost();
		node.CalculateFCost();

		// add the lowest FCost nodes to explore list - ordered
		toExplore.emplace_back(node);
	}

	toExplore.sort();

	currentNode = toExplore[0];

	toExplore.remove(0);

	// calculate neighbours in the newNode again.






}

//diagonal move is cost 14, vertical/ horizontal move is cost 10
int PathFinding::GetDistance(Node nodeA, Node nodeB)
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

