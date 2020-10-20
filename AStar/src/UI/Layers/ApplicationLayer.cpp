#include "ApplicationLayer.h"
#include "Application.h"
#include "Node.h"

#include <iostream>
#include <vector>

void ApplicationLayer::OnInit()
{
	startNode = Node(15, 20, false);
	startNode.m_Mark = 'S';
	map.Add(startNode);

	map.Init();
	map.Draw();

	map.currentNode = &startNode;

	Texture_LocationPin.loadFromFile("Assets/location.png");
	Sprite_LocationPin.setTexture(Texture_LocationPin);
	Sprite_LocationPin.setScale(0.1f, 0.1f);

	Texture_Arrow.loadFromFile("Assets/arrow.png");
	Sprite_Arrow.setTexture(Texture_Arrow);
	Sprite_Arrow.setScale(0.1f, 0.1f);
}

void ApplicationLayer::OnShutDown()
{
}

void ApplicationLayer::OnUpdate()
{
	Render();
	Update();
}

void ApplicationLayer::OnEvent(sf::Event& event)
{
}

void ApplicationLayer::Render()
{
	auto& app = Application::Get();
	auto& window = app.GetWindow();

	DrawGrid(window);
	DrawNode(window, startNode, sf::Color::Red);
	DrawNode(window, endNode, sf::Color::Green);

	Sprite_Arrow.setPosition((startNode.m_PosX * Map::NodeCellSize) + 10.f, (startNode.m_PosY * Map::NodeCellSize) + 10.f);
	Sprite_LocationPin.setPosition((endNode.m_PosX * Map::NodeCellSize) + 10.f, (endNode.m_PosY * Map::NodeCellSize) + 10.f);
	window.draw(Sprite_Arrow);
	window.draw(Sprite_LocationPin);

	DrawObstacles(window);
	// Painting the neighbours and current node isnt working :(
	/*
	DrawNode(window, *map.currentNode, sf::Color(255, 219, 88));
	for (const Node& node : map.currentNode->GetNeighbours())
	{
		DrawNode(window, node, sf::Color(255, 177, 88));
	}
	*/
	DrawPathNodes(window);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		int x = (GetMousePos(window).x - 10) / Map::NodeCellSize;
		int y = (GetMousePos(window).y - 10) / Map::NodeCellSize;
		Node obstacle(x, y, true);
		obstacle.m_Mark = 'X';
		map.Add(obstacle);
		DrawNode(window, obstacle, sf::Color(128, 128, 128));
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		map.ResetPath();
		int x = (GetMousePos(window).x - 10) / Map::NodeCellSize;
		int y = (GetMousePos(window).y - 10) / Map::NodeCellSize;
		endNode = Node(x, y, false);
		endNode.m_Mark = 'E';
		map.Add(endNode);

		while (!app.isPathFound)
		{
			p.FindPath(startNode, endNode);
		}
		map.Draw();
		app.isPathFound = false;
	}
}

void ApplicationLayer::Update()
{
	auto& app = Application::Get();
	auto& window = app.GetWindow();
}

sf::Vector2i ApplicationLayer::GetMousePos(sf::RenderWindow& window)
{
	return sf::Mouse::getPosition(window);
}

void ApplicationLayer::DrawGrid(sf::RenderWindow& window)
{
	sf::RectangleShape cell(sf::Vector2f(Map::NodeCellSize, Map::NodeCellSize));
	cell.setFillColor(sf::Color::White);
	cell.setOutlineColor(sf::Color::Black);
	cell.setOutlineThickness(3);

	for (int y = 0; y < Map::GridHeight; y++)
	{
		for (int x = 0; x < Map::GridWidth; x++)
		{
			float cx = (x * Map::NodeCellSize) + 10.f;
			float cy = (y * Map::NodeCellSize) + 10.f;
			cell.setPosition(sf::Vector2f(cx, cy));
			window.draw(cell);
		}
	}
}

void ApplicationLayer::DrawNode(sf::RenderWindow& window, Node node, sf::Color color)
{
	sf::RectangleShape cell(sf::Vector2f(Map::NodeCellSize, Map::NodeCellSize));
	cell.setFillColor(color);
	cell.setOutlineColor(sf::Color::Black);
	cell.setOutlineThickness(3);

	float cx = (node.m_PosX * Map::NodeCellSize) + 10.f;
	float cy = (node.m_PosY * Map::NodeCellSize) + 10.f;

	cell.setPosition(sf::Vector2f(cx, cy));

	window.draw(cell);
}

void ApplicationLayer::DrawObstacles(sf::RenderWindow& window)
{
	std::vector<Node> obstacles = map.GetObstacles();

	for (const Node& obstacle : obstacles)
	{
		DrawNode(window, obstacle, sf::Color(128, 128, 128));

		float cx = (obstacle.m_PosX * Map::NodeCellSize) + 10.f;
		float cy = (obstacle.m_PosY * Map::NodeCellSize) + 10.f;

	}
}

void ApplicationLayer::DrawPathNodes(sf::RenderWindow& window)
{
	std::vector<Node> pathNodes = map.GetPathNodes();

	for (const Node& pathNode : pathNodes)
	{
		DrawNode(window, pathNode, sf::Color(135, 206, 235));
	}
}
