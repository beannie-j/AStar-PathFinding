#pragma once
#include "Node.h"

class PathFinding
{
private:
	void FindPath(Node startNode, Node targetNode);
	int GetDistance(Node A, Node B);
};

