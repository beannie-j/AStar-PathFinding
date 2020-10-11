#pragma once
#include "Node.h"

class PathFinding
{
public:
	void FindPath(Node startNode, Node targetNode);
	int GetDistance(Node A, Node B);
	int CalculateGCost(Node& node, const Node& startNode);
	int CalculateHCost(Node& node, const Node& endNode);
	int CalculateFCost(Node& node);

	PathFinding() = default;
};

