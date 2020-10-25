#pragma once
#include "Layer.h"
#include "PathFinding.h"
#include "Map.h" 
#include "Timestep.h"

#include <SFML/Graphics.hpp>

class ApplicationLayer : public Layer
{
public:
	virtual void OnInit() override;
	virtual void OnShutDown() override;

	virtual void OnUpdate(Timestep ts) override;
	virtual void OnEvent(sf::Event& event) override;

private:
	static bool running;

	Node startNode;
	Node endNode;
	PathFinding p;
	Map map;

	const float Block_Size = 40;

	sf::Texture Texture_LocationPin;
	sf::Sprite Sprite_LocationPin;

	sf::Texture Texture_Arrow;
	sf::Sprite Sprite_Arrow;

	void Render(Timestep ts);
	void Update(Timestep ts);

	sf::Vector2i GetMousePos(sf::RenderWindow& window);
	void DrawGrid(sf::RenderWindow& window);
	void DrawNode(sf::RenderWindow& window, Node node, sf::Color color);
	void DrawObstacles(sf::RenderWindow& window);
	void DrawPathNodes(sf::RenderWindow& window);
	void DrawVisitedNodes(sf::RenderWindow& window);

};

