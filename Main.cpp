#include <iostream>

#include "Map.h"
#include "PathFinding.h"
#include "Node.h"

int main()
{
	PathFinding p;

	Node start(2, 0);
	start.mark = 'S';
	Node end(0, 5);
	end.mark = 'E';

	p.FindPath(start, end);

	//Map map;

	//map.Add(start);
	//map.Add(end);

	//map.Draw();

	
}
