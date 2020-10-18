#include <iostream>

#include "Map.h"
#include "PathFinding.h"
#include "Node.h"

#include <SFML/Graphics.hpp>

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

	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}
}
