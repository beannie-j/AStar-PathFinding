#include "ApplicationLayer.h"
#include "Application.h"
#include "Node.h"

#include <iostream>
#include <vector>

void ApplicationLayer::OnInit()
{
	//running = true;

	startNode = Node(15, 20, false);
	startNode.m_Mark = 'S';
	//Node start(3, 8, false);
	//Node start(9, 2, false);
	//Node start(15, 8, false);

	endNode = Node(4, 2, false);
	endNode.m_Mark = 'E';
	map.Add(startNode);
	map.Add(endNode);

	Node obstacle1(3, 3, true);
	obstacle1.m_Mark = 'X';

	Node obstacle2(5, 3, true);
	obstacle2.m_Mark = 'X';

	Node obstacle3(3, 1, true);
	obstacle3.m_Mark = 'X';

	Node obstacle4(5, 2, true);
	obstacle4.m_Mark = 'X';

	Node obstacle5(6, 2, true);
	obstacle5.m_Mark = 'X';

	map.Init();
	map.Add(obstacle1);
	map.Add(obstacle2);
	map.Add(obstacle3);
	map.Add(obstacle4);
	map.Add(obstacle5);

	map.Draw();

	map.currentNode = &startNode;
}

void ApplicationLayer::OnShutDown()
{
}

void ApplicationLayer::OnUpdate()
{
	auto& app = Application::Get();
	sf::RenderWindow& window = app.GetWindow();

	DrawGrid(window);

	DrawNode(window, startNode, sf::Color::Red);
	DrawNode(window, endNode, sf::Color::Green);

	DrawObstacles(window);

	DrawNode(window, *map.currentNode, sf::Color::White);

	while (!app.isPathFound)
	{
		std::cout << "*Current Node :";
		map.currentNode->Print();
		p.FindPath(startNode, endNode);
	}

	DrawPathNodes(window);
}

void ApplicationLayer::OnEvent(sf::Event& event)
{
}

void ApplicationLayer::DrawGrid(sf::RenderWindow& window)
{
	sf::RectangleShape cell(sf::Vector2f(Map::NodeCellSize, Map::NodeCellSize));
	cell.setFillColor(sf::Color::Black);
	cell.setOutlineColor(sf::Color::White);
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
	cell.setOutlineColor(sf::Color::White);
	cell.setOutlineThickness(1);

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

		sf::Text text;
		sf::Font font;
		std::string string = "X";
		font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");
		text.setFont(font);
		text.setFillColor(sf::Color::Red);
		text.setCharacterSize(20);

		float cx = (obstacle.m_PosX * Map::NodeCellSize) + 10.f;
		float cy = (obstacle.m_PosY * Map::NodeCellSize) + 10.f;

		text.setPosition(sf::Vector2f(cx, cy));

		window.draw(text);
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
