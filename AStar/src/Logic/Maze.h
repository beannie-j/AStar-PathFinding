#pragma once

#include <array>
#include <optional>
#include <stack>
#include <vector>

#include "Node.h"

class Maze
{
private:
	std::stack<Node> m_PathStack;
	std::vector<Node> m_PathVector;
	std::vector<Node> m_Visited;
	bool m_MazeGenerated = false;
	int m_NumVisitedCells = 1;
	Node m_StartNode;

public:
	void BeginMaze(const Node& startNode);
	bool NextStep();
	void EndMazeGenerating();

	std::vector<Node> GetNeighboursNonDiagonal(Node node);
	bool Contains(std::vector<Node> vec, Node node);

	bool IsMazeGenerated() const { return m_MazeGenerated; }

	const std::vector<Node>& GetPathVector() const { return m_PathVector; }
	const std::vector<Node>& GetVisited() const { return m_Visited; }

};

