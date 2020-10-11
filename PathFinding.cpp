#include "PathFinding.h"

#include <vector>
#include <unordered_set>
#include <cmath>
#include <algorithm>
#include <iostream>

bool cmp(Node nodeA, Node nodeB) { return (nodeA.m_FCost < nodeB.m_FCost); }

void PathFinding::FindPath(Node startNode, Node endNode)
{
	Node currentNode = startNode;
	std::vector<Node> neighbours = currentNode.GetNeighbours();
	std::vector<Node> toExplore;
	//std::unordered_set<Node> visited;

	for (Node node : neighbours)
	{
		// Calculate all travel costs.
		CalculateGCost(node, startNode);
		CalculateHCost(node, endNode);
		CalculateFCost(node);

		// add the lowest FCost nodes to explore list - ordered
		toExplore.emplace_back(node);
	}

	// sort the toExplore vector by FCost
	std::sort(toExplore.begin(), toExplore.end(), cmp);

	std::cout << "toExplore vector contains:\n";
	int i = 0;
	for (auto it = toExplore.begin(); it != toExplore.end(); ++it)
	{
		std::cout << i << " : [" << it->m_PosX << " , " << it->m_PosY << "] GCost: " << it->m_GCost << " HCost: " << it->m_HCost << " FCost: " << it->m_FCost << '\n';
		i++;
	}

	//toExplore.remove(0);

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

int PathFinding::CalculateGCost(Node& node, const Node& startNode)
{
	node.m_GCost = GetDistance(node, startNode);
	return node.m_GCost;
}

int PathFinding::CalculateHCost(Node& node, const Node& endNode)
{
	node.m_HCost = GetDistance(node, endNode);
	return node.m_HCost;
}

int PathFinding::CalculateFCost(Node& node)
{
	node.m_FCost = node.m_GCost + node.m_HCost;
	return node.m_FCost;
}

