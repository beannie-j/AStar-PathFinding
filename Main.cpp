#include <iostream>

#include "Map.h"
#include "PathFinding.h"
#include "Node.h"

int main()
{
	PathFinding p;

	Node start(7, 4, false);
	start.mark = 'S';
	Node end(4, 2, false);
	end.mark = 'E';

	Map map;

	p.FindPath(start, end);

	//Map map;

	//map.Add(start);
	//map.Add(end);

	//map.Draw();
}
