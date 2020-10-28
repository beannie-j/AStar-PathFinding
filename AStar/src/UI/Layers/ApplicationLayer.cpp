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

	sf::Font font;
	font.loadFromFile("C:\\Fonts\\Arial.ttf");
	m_NextStepButton = std::make_unique<Button>(50, 50, 80, 30, font, "Next Step", 16, sf::Color::White, sf::Color::White);
} 

void ApplicationLayer::OnShutDown()
{
}

static float s_PathTime = 0.02f;
static float s_PathTimer = s_PathTime;

void ApplicationLayer::OnUpdate(Timestep ts)
{
	Render(ts);
	Update(ts);

	if (m_BeginPathFinding)
	{
		s_PathTimer -= ts;
		if (s_PathTimer < 0.0f)
		{
			if (m_Path.NextStep())
			{
				if (m_Path.IsPathFound())
				{
					// path found!
				}
				else
				{
					// no path found
				}
				m_BeginPathFinding = false;
			}
			s_PathTimer = s_PathTime;
		}
	}

	// Process timed functions
	//std::cout << "Delta time: {0}s {1}ms " << ts.GetSeconds() << " " << ts.GetMilliseconds() << std::endl;
	for (auto it = m_TimedFunctionQueue.begin(); it != m_TimedFunctionQueue.end(); )
	{
		auto& tf = *it;
		tf.Time -= ts.GetSeconds();
		//std::cout << tf.Time << std::endl;
		if (tf.Time <= 0.0f)
		{
			tf.Function();
			it = m_TimedFunctionQueue.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void ApplicationLayer::OnEvent(sf::Event& event)
{
	auto& app = Application::Get();
	auto& window = app.GetWindow();

	int x = (GetMousePos(window).x - 10) / Map::NodeCellSize;
	int y = (GetMousePos(window).y - 10) / Map::NodeCellSize;

	bool startNodeBounds = (x == startNode.m_PosX && y == startNode.m_PosY);
	bool endNodeBounds = (x == endNode.m_PosX && y == endNode.m_PosY);

	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Space)
		{
			m_BeginPathFinding = true;

			if (m_Path.NextStep())
			{
				if (m_Path.IsPathFound())
				{
					// path found!
				}
				else
				{
					// no path found
				}
			}
		}
	}


	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		int x = (GetMousePos(window).x - 10) / Map::NodeCellSize;
		int y = (GetMousePos(window).y - 10) / Map::NodeCellSize;
		//std::cout << "x " << x << "y " << y << std::endl;

		if (!startNodeBounds && !endNodeBounds)
		{
			Node obstacle(x, y, true);
			obstacle.m_Mark = 'X';
			map.Add(obstacle);
			DrawNode(window, obstacle, sf::Color(128, 128, 128));
		}

		if (startNodeBounds)
		{
			std::cout << "Start node\n";
		}

		if (endNodeBounds)
		{
			std::cout << "End node\n";
		}
	}
}

void ApplicationLayer::DrawPath(sf::RenderWindow& window)
{
	const auto& openSet = m_Path.GetOpenSet();
	const auto& closedSet = m_Path.GetClosedSet();

	for (const auto& node : openSet)
	{
		DrawNode(window, node, sf::Color::Green);
	}

	for (const auto& node : closedSet)
	{
		DrawNode(window, node, sf::Color::Red);
	}

}

void ApplicationLayer::Render(Timestep ts)
{
	auto& app = Application::Get();
	auto& window = app.GetWindow();

	PathFindingResult result;

	DrawGrid(window);

	DrawNode(window, startNode, sf::Color::Red);
	DrawNode(window, endNode, sf::Color::Green);

	DrawPath(window);

	Sprite_Arrow.setPosition((startNode.m_PosX * Map::NodeCellSize) + 10.f, (startNode.m_PosY * Map::NodeCellSize) + 10.f);
	Sprite_LocationPin.setPosition((endNode.m_PosX * Map::NodeCellSize) + 10.f, (endNode.m_PosY * Map::NodeCellSize) + 10.f);
	window.draw(Sprite_Arrow);
	window.draw(Sprite_LocationPin);

	m_NextStepButton->DrawButton(window);

	DrawObstacles(window);
	//DrawVisitedNodes(window);
	//DrawPathNodes(window);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
	{
		std::cout << " Middle pressed" << std::endl;
		m_TimedFunctionQueue.push_back({ 2.0f, [&]() { std::cout << "Hello!\n"; } });
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		map.ResetPath();
		int x = (GetMousePos(window).x - 10) / Map::NodeCellSize;
		int y = (GetMousePos(window).y - 10) / Map::NodeCellSize;
		endNode = Node(x, y, false);
		endNode.m_Mark = 'E';
		map.Add(endNode);
		
		p.FindPath(startNode, endNode);
		map.Draw();

		m_Path.BeginPathFinding(startNode, endNode);
	}

}

void ApplicationLayer::Update(Timestep ts)
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
		//m_TimedFunctionQueue.push_back({ 2.0f, [&]() { DrawNode(window, pathNode, sf::Color(135, 206, 235)); } });
		DrawNode(window, pathNode, sf::Color(135, 206, 235));
	}
}

void ApplicationLayer::DrawVisitedNodes(sf::RenderWindow& window)
{
	std::vector<Node> visitedNodes = map.GetVisitedNodes();

	for (const Node& v : visitedNodes)
	{
		//m_TimedFunctionQueue.push_back({ 2.0f, [&]() { DrawNode(window, v, sf::Color(255, 177, 88)); } });
		DrawNode(window, v, sf::Color(255, 177, 88));
	}
}