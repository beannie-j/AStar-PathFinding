#include "PathFinding.h"
#include "Map.h"

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

	Node obstacle1(3, 2, true);
	obstacle1.mark = 'X';

	Node obstacle2(4, 3, true);
	obstacle2.mark = 'X';

	//auto& map = Map::Get();
	//map.Init();

	Map map;
	map.Init();
	map.Add(startNode);
	map.Add(endNode);
	map.Add(obstacle1);
	map.Add(obstacle2);
	map.Draw();

	while (currentNode != endNode)
	{
		std::cout << "*Current node* ";
		currentNode.Print();
		neighbours = currentNode.GetNeighbours();
		toExplore.erase(toExplore.begin(), toExplore.end());

		for (Node& node : neighbours)
		{
			// Calculate all travel costs.
			CalculateGCost(node, startNode);
			node.m_HCost = CalculateHCost(endNode);
			CalculateFCost(node);

			node.CalculateCosts(startNode, endNode);
			// g, h, f

			// add the lowest FCost nodes to explore list
			toExplore.emplace_back(node);
		}
		
		// sort the list so that we can get the smallest fCost and hCost neighbour
		std::sort(toExplore.begin(), toExplore.end(), [](auto& nodeA, auto& nodeB)
		{
			return (nodeA.m_FCost < nodeB.m_FCost ||
				nodeA.m_FCost == nodeB.m_FCost &&
				nodeA.m_HCost < nodeB.m_HCost);
		});

		std::cout << "toExplore vector contains:\n";
		for (const Node& node : toExplore)
		{
			node.Print();
		}

		// currentNode set to first element in toExplore list - most path efficient node.

		/*
			Missing part where if other path has better FCost values it needs to retrace and come back.
			F costs are increasing if you are not going in a straight line. Even though the H costs are decreasing F costs will be increasing a lot more.
			if F cost keeps increasing you need to look at other options. 

			*/
		currentNode = toExplore.at(0);

		// mark that node as visited
		currentNode.mark = '*';
		visited.push_back(currentNode);
		map.Add(currentNode);

		if (currentNode == endNode)
		{
			std::cout << "reached destination\n *Current Node* ";
			currentNode.Print();
			map.Add(endNode);
			map.Draw();

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

