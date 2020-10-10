#include "PathFinding.h"

#include <vector>
#include <unordered_set>

void PathFinding::FindPath(Node startNode, Node targetNode)
{
	std::vector<Node> Opened;
	std::unordered_set<Node> Closed();

	// add startNode to Open Nodes
	Opened.push_back(startNode);

	while (Opened.size() > 0)
	{
		Node currentNode = Opened[0];

	}
}
