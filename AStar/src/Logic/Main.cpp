#include <iostream>
#include <SFML/Graphics.hpp>

#include "Map.h"
#include "PathFinding.h"
#include "Node.h"
#include "Application.h"

int main()
{
	PathFinding p;
	
	//width 20, height 10

	//Node start(3, 8, false);
	Node start(7, 4, false);
	//Node start(9, 2, false);
	//Node start(15, 8, false);

	start.mark = 'S';
	Node end(4, 2, false);
	end.mark = 'E';

	Map map;

	p.FindPath(start, end);

	//Map map;

	//map.Add(start);
	//map.Add(end);

	//map.Draw();

	Application application;
	application.Init();
	application.Run();
	application.ShutDown();
	
}
