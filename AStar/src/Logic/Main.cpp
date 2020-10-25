#include <iostream>
#include <SFML/Graphics.hpp>

#include "Map.h"
#include "PathFinding.h"
#include "Node.h"
#include "Application.h"

int main()
{
	//PathFinding p;	
	//width 20, height 10

	//Map map;

	//map.Add(start);
	//map.Add(end);

	//map.Draw();

	Application application;
	application.Init();
	application.Run();
	application.ShutDown();
	
}
