#include <iostream>
#include <SFML/Graphics.hpp>

#include "Map.h"
#include "PathFinding.h"
#include "Node.h"
#include "Application.h"

int main()
{
	Application application;
	application.Init();
	application.Run();
	application.ShutDown();
	
}
