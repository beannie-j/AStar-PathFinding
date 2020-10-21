#include "PathFinding.h"
#include "Map.h"
#include "Application.h"

#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>

bool cmp(Node nodeA, Node nodeB) { return (nodeA.m_FCost < nodeB.m_FCost || nodeA.m_FCost == nodeB.m_FCost && nodeA.m_HCost < nodeB.m_HCost); }

bool PathFinding::FindPath(const Node& startNode, const Node& endNode)
{
	std::vector<Node> neighbours;
	std::vector<Node> openSet;
	std::vector<Node> closedSet;

	auto& app = Application::Get();
	auto& map = Map::Get();

	openSet.push_back(startNode);

	while (!openSet.empty())
	{
		std::sort(openSet.begin(), openSet.end(), [](auto& nodeA, auto& nodeB)
			{
				return (nodeA.m_FCost < nodeB.m_FCost ||
					nodeA.m_FCost == nodeB.m_FCost &&
					nodeA.m_HCost < nodeB.m_HCost);
			});

		Node currentNode = openSet[0];
		map.currentNode = &currentNode;

		openSet.erase(std::remove(openSet.begin(), openSet.end(), currentNode), openSet.end());
		closedSet.push_back(currentNode);

		auto neighbours = currentNode.GetNeighbours();
		for (Node& neighbour : neighbours)
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
				{
					openSet.push_back(neighbour);
				}
			}
			map.Add(currentNode);
		}

		

		if (currentNode == endNode)
		{
			if (RetracePath(startNode, endNode))
			{
				app.isPathFound = true;
				return true;
			}
			return false;
		}
	}
	return false;
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

bool PathFinding::Contains(std::vector<Node> vec, Node _node)
{
	for (const Node& node : vec)
	{
		if (node == _node) // if they have same x and y coordinates.
		{	// compare parents
			if (node.m_Parent != nullptr && _node.m_Parent != nullptr)
			{
				if (node.m_Parent == _node.m_Parent) return true;
			}
		}
	}
	return false;
}

bool PathFinding::RetracePath(const Node& startNode, const Node& endNode)
{
	auto& map = Map::Get();
	auto& grid = map.GetGrid();

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
		node.m_Mark = 'P';
		map.Add(node);
		node.Print();
	}

	map.Add(endNode);
	map.Draw();

	if (*path[path.size() - 1].m_Parent == startNode)
	{
		return true;
	}

	return false;
}