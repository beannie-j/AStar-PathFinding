#include <iostream>

#include "Map.h"
#include "PathFinding.h"
#include "Node.h"

int main()
{
	PathFinding p;
	Node start(2, 0);
	Node end(0, 5);

	p.FindPath(start, end);

	
}
