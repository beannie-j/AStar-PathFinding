#include <iostream>

#include "Map.h"
#include "PathFinding.h"
#include "Node.h"

int main()
{
	PathFinding p;

	Node start(1, 0, false);
	start.mark = 'S';
	Node end(5, 5, false);
	end.mark = 'E';

	p.FindPath(start, end);

	//Map map;

	//map.Add(start);
	//map.Add(end);

	//map.Draw();
}
