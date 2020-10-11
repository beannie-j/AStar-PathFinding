#include <iostream>

#include "Map.h"
#include "PathFinding.h"
#include "Node.h"

int main()
{
	PathFinding p;
	Node node(0, 0);
	Node start(1, 1);
	Node end(5, 5);
	p.CalculateGCost(node, start); // prints 20

	std::cout << node.m_GCost << std::endl;

	p.FindPath(start, end);
	
}
