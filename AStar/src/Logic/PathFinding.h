#pragma once
#include "Node.h"

#include <vector>

struct PathFindingResult
{
	bool pathFound = false;
	std::vector<Node> closedSet;
};

class Path
{
public:
	void BeginPathFinding(const Node& startNode, const Node& endNode);
	// Returns true if searching has completed
	bool NextStep();
	void EndPathFinding();

	bool IsPathFound() const { return m_PathFound; }

	const std::vector<Node>& GetOpenSet() const { return m_OpenSet; }
	const std::vector<Node>& GetClosedSet() const { return m_ClosedSet; }
	const std::vector<Node>& GetPathSet() const { return m_PathSet; }

private:
	int CalculateGCost(Node& node, const Node& startNode);
	int CalculateHCost(Node& node, const Node& endNode);
	int CalculateFCost(Node& node);
	bool Contains(std::vector<Node> vec, Node node);
	int GetDistance(const Node& nodeA, const Node& nodeB) const;
	bool RetracePath(const Node& startNode, const Node& endNode);
private:
	Node m_StartNode, m_EndNode;
	std::vector<Node> m_OpenSet;
	std::vector<Node> m_ClosedSet;
	std::vector<Node> m_PathSet;
	bool m_PathFound = false;
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
private:
};