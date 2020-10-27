#pragma once
#include "Node.h"

#include <vector>

struct PathFindingResult
{
	bool pathFound = false;
	std::vector<Node> closedSet;
};

class PathFinding
{
public:

	std::vector<Node> path;

	PathFindingResult FindPath(const Node& startNode, const Node& endNode);
	int GetDistance(Node A, Node B);
	int CalculateGCost(Node& node, const Node& startNode);
	int CalculateHCost(Node& node, const Node& endNode);
	int CalculateFCost(Node& node);
	bool Contains(std::vector<Node> vec, Node node);
	bool RetracePath(const Node& startNode, const Node& endNode);

	PathFinding() = default;
};
