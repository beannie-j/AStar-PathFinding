#pragma once
#include "Layer.h"
#include "PathFinding.h"
#include "Map.h" 
#include "Timestep.h"
#include "Maze.h"

#include <SFML/Graphics.hpp>
#include <queue>
#include <functional>

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

	sf::Clock clock;

	sf::Texture Texture_LocationPin;
	sf::Sprite Sprite_LocationPin;

	sf::Texture Texture_Arrow;
	sf::Sprite Sprite_Arrow;

	Path m_Path;
	Maze m_Maze;

	float m_LastFrameTime = 0.0f;
	bool m_BeginPathFinding = false; 
	bool m_BeginDrawMaze = false;

	struct TimedFunction
	{
		float Time = 0.0f;
		std::function<void()> Function;
	};

	std::vector<TimedFunction> m_TimedFunctionQueue;

	void Render(Timestep ts);
	void Update(Timestep ts);

	sf::Vector2i GetMousePos(sf::RenderWindow& window);
	void DrawGrid(sf::RenderWindow& window);
	void DrawNode(sf::RenderWindow& window, Node node, sf::Color color);
	void CarvePath(sf::RenderWindow& window, Node node);
	void DrawObstacles(sf::RenderWindow& window);
	void DrawPathNodes(sf::RenderWindow& window);
	void DrawVisitedNodes(sf::RenderWindow& window);
	void DrawWalls(sf::RenderWindow& window);


	void DrawPath(sf::RenderWindow& window);

};

