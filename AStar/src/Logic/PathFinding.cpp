#include "PathFinding.h"
#include "Map.h"

#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>

bool cmp(Node nodeA, Node nodeB) { return (nodeA.m_FCost < nodeB.m_FCost || nodeA.m_FCost == nodeB.m_FCost && nodeA.m_HCost < nodeB.m_HCost); }

void PathFinding::FindPath(Node& startNode, Node& endNode)
{
	std::vector<Node> neighbours;
	std::vector<Node> openSet;
	std::vector<Node> closedSet;
	std::vector<Node> path;

	Node obstacle1(3, 3, true);
	obstacle1.mark = 'X';

	Node obstacle2(5, 3, true);
	obstacle2.mark = 'X';

	Node obstacle3(3, 1, true);
	obstacle3.mark = 'X';

	Node obstacle4(5, 2, true);
	obstacle4.mark = 'X';

	Node obstacle5(6, 2, true);
	obstacle5.mark = 'X';

	auto& map = Map::Get();

	map.Init();
	//startNode.m_Parent = &Node(0, 0, false);
	map.Add(startNode);

	//endNode.m_Parent = &Node(0, 0, false);
	map.Add(endNode);

	map.Add(obstacle1);
	map.Add(obstacle2);
	map.Add(obstacle3);
	map.Add(obstacle4);
	map.Add(obstacle5);
	map.Draw();

	openSet.push_back(startNode);

	while (!openSet.empty())
	{
		Node currentNode = openSet[0];
		
		for (int i = 1; i < openSet.size(); i++) {
			if (openSet[i].m_FCost < currentNode.m_FCost || openSet[i].m_FCost == currentNode.m_FCost) {
				if (openSet[i].m_HCost < currentNode.m_HCost)
					currentNode = openSet[i];
			}
		}
		
		currentNode.Print();
		/*
		std::sort(openSet.begin(), openSet.end(), [](auto& nodeA, auto& nodeB)
			{
				return (nodeA.m_FCost < nodeB.m_FCost ||
					nodeA.m_FCost == nodeB.m_FCost &&
					nodeA.m_HCost < nodeB.m_HCost);
			});
			*/

		//

		openSet.erase(std::remove(openSet.begin(), openSet.end(), currentNode), openSet.end());
		closedSet.push_back(currentNode);

		for (Node& neighbour : currentNode.GetNeighbours())
		{
			
			if (neighbour.m_IsObstacle || Contains(closedSet, neighbour)) continue;
			// Calculate all travel costs.
			CalculateGCost(neighbour, startNode);
			CalculateHCost(neighbour, endNode);
			CalculateFCost(neighbour);

			int newCostToNeighbour = currentNode.m_GCost + GetDistance(currentNode, neighbour);

			if (newCostToNeighbour < neighbour.m_GCost || !Contains(openSet, neighbour))
			{
				neighbour.m_GCost = newCostToNeighbour;
				neighbour.m_HCost = CalculateHCost(neighbour, endNode);
				CalculateFCost(neighbour);
				neighbour.m_Parent = new Node(currentNode.m_PosX, currentNode.m_PosY, false);

				if (!Contains(openSet, neighbour))
					openSet.push_back(neighbour);
			}
			map.Add(currentNode);
			currentNode.Print();
		}

		if (currentNode == endNode)
		{
			//currentNode.Print();
			RetracePath(startNode, endNode);
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

bool PathFinding::Contains(std::vector<Node> vec, Node node)
{
	if (std::find(vec.begin(), vec.end(), node) != vec.end())
	{
		std::cout << " Contains true ";
		node.Print();
		/* v contains x */
		return true;
	}
	else /* v does not contain x */
		return false;
}

bool PathFinding::RetracePath(Node& startNode, Node& endNode)
{
	std::cout << "Map: \n";

	auto& map = Map::Get();
	auto& grid = map.GetGrid();


	for (int y = 0; y < Map::GridHeight; y++)
	{
		for (int x = 0; x < Map::GridWidth; x++)
		{
			if (grid[x + y * Map::GridWidth].m_Parent)
			{
				grid[x + y * Map::GridWidth].Print();
			}
		}
		std::cout << "\n";
	}
	std::cout << "Path: \n";

	std::vector<Node> path;
	Node currentNode = map.GetNode(endNode.m_PosX, endNode.m_PosY); // endNode

	while (currentNode != startNode)
	{
		path.push_back(currentNode);
		currentNode = map.GetNode(currentNode.m_Parent->m_PosX, currentNode.m_Parent->m_PosY);
	}

	for (Node& node : path)
	{
		node.mark = 'P';
		map.Add(node);
		node.Print();

	}

	map.Add(endNode);
	map.Draw();

	return false;
}