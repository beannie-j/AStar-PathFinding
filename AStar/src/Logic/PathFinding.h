#pragma once
#include "Node.h"

#include <vector>

class PathFinding
{
public:

	std::vector<Node> path;

	void FindPath(Node& startNode, Node& endNode);
	int GetDistance(Node A, Node B);
	int CalculateGCost(Node& node, const Node& startNode);
	int CalculateHCost(Node& node, const Node& endNode);
	int CalculateFCost(Node& node);
	bool Contains(std::vector<Node> vec, Node node);
	bool RetracePath(Node& startNode, Node& endNode);

	PathFinding() = default;
};

