#include "PathFinding.h"

#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>

bool cmp(Node nodeA, Node nodeB) { return (nodeA.m_FCost < nodeB.m_FCost || nodeA.m_FCost == nodeB.m_FCost && nodeA.m_HCost < nodeB.m_HCost); }

void PathFinding::FindPath(Node startNode, Node endNode)
{
	// while toExplore list is not empty keep looping.
	Node currentNode = startNode;
	std::vector<Node> neighbours;
	std::vector<Node> toExplore;
	std::vector<Node> visited;

	//toExplore.push_back(startNode);

	while (currentNode != endNode)
	{
		std::cout << "*Current node* ";
		currentNode.Print();
		neighbours = currentNode.GetNeighbours();
		toExplore.erase(toExplore.begin(), toExplore.end());

		for (Node node : neighbours)
		{
			// Calculate all travel costs.
			CalculateGCost(node, startNode);
			CalculateHCost(node, endNode);
			CalculateFCost(node);

			// add the lowest FCost nodes to explore list
			toExplore.emplace_back(node);
		}
		
		// sort the list so that we can get the smallest fCost and hCost neighbour
		std::sort(toExplore.begin(), toExplore.end(), cmp);

		std::cout << "toExplore vector contains:\n";
		for (const auto& node : toExplore)
		{
			node.Print();
		}
		
		currentNode = toExplore.at(0);
		// currentNode moves to first element in toExplore list
		// mark that node as visited
		visited.push_back(currentNode);
		i++;

		if (currentNode == endNode)
		{
			std::cout << "reached destination\n";
			currentNode.Print();
			return;
		}
	}
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

