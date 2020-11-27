#include "ApplicationLayer.h"
#include "Application.h"
#include "Node.h"
#include "Maze.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>

void ApplicationLayer::OnInit()
{
	startNode = Node(3, 1, false, false);
	startNode.m_Mark = 'S';
	map.Add(startNode);

	map.Init();

	map.currentNode = &startNode;

	map.ResetPath();
	endNode.m_Mark = 'E';
	map.Add(endNode);

	map.Draw();

	Texture_LocationPin.loadFromFile("Assets/location.png");
	Sprite_LocationPin.setTexture(Texture_LocationPin);
	Sprite_LocationPin.setScale(0.1f, 0.1f);

	Texture_Arrow.loadFromFile("Assets/arrow.png");
	Sprite_Arrow.setTexture(Texture_Arrow);
	Sprite_Arrow.setScale(0.1f, 0.1f);

	sf::Font font;
	font.loadFromFile("C:\\Fonts\\Arial.ttf");
} 

void ApplicationLayer::OnShutDown()
{
}

static float s_PathTime = 0.01f; 
static float s_PathTimer = s_PathTime;

struct PathData
{
	int NodeX = 0, NodeY = 0;
	int Dir = 0;
};

static PathData s_LastPathNode;

static std::vector<std::pair<int, int>> s_PathCoords;

static void TryPlaceWall(Map& map, int x, int y)
{
	auto& it = std::find_if(s_PathCoords.begin(), s_PathCoords.end(), [x, y](auto& pair) { return std::get<0>(pair) == x && std::get<1>(pair) == y; });
	if (it == s_PathCoords.end()) // not found
	{
		//map.Add(Node(x, y, false, true)); // changed to Wall Node
		Node node(x, y, true, false);
		node.m_Mark = 'W';
		map.Add(node);
	}
}

void ApplicationLayer::OnUpdate(Timestep ts)
{
	auto& app = Application::Get();
	auto& window = app.GetWindow();
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
					// path found
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

	if (m_BeginDrawMaze)
	{
		s_PathTimer -= ts;
		if (s_PathTimer < 0.0f)
		{
			if (m_Maze.NextStep())
			{
				
				if (m_Maze.IsMazeGenerated())
				{
					// path found
				}
				else
				{
					// no path found
				}
				m_BeginDrawMaze = false;
				m_Maze.EndMazeGenerating();
				startNode.m_Mark = 'S';
				map.Add(startNode);
				endNode.m_Mark = 'E';
				map.Add(endNode);
			}
			else
			{
				auto& node = m_Maze.GetLastVisited();

				if (s_LastPathNode.NodeX)
				{
					switch (s_LastPathNode.Dir)
					{
					case 0: // left
					case 2: // Right
						TryPlaceWall(map, s_LastPathNode.NodeX, s_LastPathNode.NodeY + 1);
						TryPlaceWall(map, s_LastPathNode.NodeX, s_LastPathNode.NodeY - 1);
						break;
					case 1: // Down
					case 3: // Up
						TryPlaceWall(map, s_LastPathNode.NodeX + 1, s_LastPathNode.NodeY);
						TryPlaceWall(map, s_LastPathNode.NodeX - 1, s_LastPathNode.NodeY);
						break;
					}

					map.Add(Node(s_LastPathNode.NodeX, s_LastPathNode.NodeY, false, false));
				}

				s_PathCoords.emplace_back(node.m_PosX, node.m_PosY);

				s_LastPathNode.NodeX = node.m_PosX;
				s_LastPathNode.NodeY = node.m_PosY;
				s_LastPathNode.Dir = node.GetDir();
			}
			s_PathTimer = s_PathTime;
		}
	}

	for (auto it = m_TimedFunctionQueue.begin(); it != m_TimedFunctionQueue.end(); )
	{
		auto& tf = *it;
		tf.Time -= ts.GetSeconds();
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

static bool dragging = false;
static bool movingStartNode = false;
static bool movingEndNode = false;

sf::Vector2i ApplicationLayer::GetMousePos(sf::RenderWindow& window)
{
	return sf::Mouse::getPosition(window);
}

struct DragData
{
	Node* DragNode = nullptr;
	std::pair<int, int> OriginCoords;

	operator bool() { return DragNode; }
};

DragData s_DragData;

static void BeginDrag(Node* node)
{
	if (s_DragData)
	{
		//assert
	}
	s_DragData = { node, { node->m_PosX, node->m_PosY } };

}

static void UpdateDrag(sf::RenderWindow& window)
{
	if (!s_DragData)
		return;

	//HZ_ASSERT(s_DragData, "Drag data must be true!");
	/*
	int mousePosX = sf::Mouse::getPosition(window).x;
	int mousePosY = sf::Mouse::getPosition(window).y;

	int screenPosX = (int)(mousePosX - 10) / Map::NodeCellSize;
	int screenPosY = (int)(mousePosY - 10) / Map::NodeCellSize;

	s_DragData.DragNode->m_PosX = screenPosX;
	s_DragData.DragNode->m_PosY = screenPosY;

	*/

}

static void EndDrag()
{
	// read from drag data



	s_DragData.DragNode = nullptr;
}

void ApplicationLayer::OnEvent(sf::Event& event)
{
	auto& app = Application::Get();
	auto& window = app.GetWindow();

	int mousePosX = (int)(GetMousePos(window).x - 10) / Map::NodeCellSize;
	int mousePosY = (int)(GetMousePos(window).y - 10) / Map::NodeCellSize;

	static std::set<std::pair<int, int>> s_PathCoords;
	
	if (s_DragData)
	{
		UpdateDrag(window);
	}

	if (event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonPressed)
	{
		bool startNodeBounds = (mousePosX == startNode.m_PosX && mousePosY == startNode.m_PosY);
		movingStartNode = startNodeBounds;

		if (movingStartNode)
		{
			dragging = true;
			BeginDrag(&startNode);
		}

		bool endNodeBounds = (mousePosX == endNode.m_PosX && mousePosY == endNode.m_PosY);
		movingEndNode = endNodeBounds;

		if (movingEndNode)
		{
			dragging = true;
			BeginDrag(&endNode);
		}
	}

	if (dragging)
	{
		s_PathCoords.insert(std::make_pair(mousePosX, mousePosY));	
		//std::cout << "*******adding  " << mousePosX << " , " << mousePosY << std::endl;
		auto last = *s_PathCoords.rbegin();
		//std::cout << last.first << " , " << last.second << std::endl;

	}

	if (event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonReleased && dragging)
	{
		if (movingStartNode)
		{
			if (!map.GetNode(mousePosX, mousePosY).m_IsObstacle)
			{
				startNode.m_PosX = mousePosX;
				startNode.m_PosY = mousePosY;
			}
			else
			{
				//std::cout << s_PathCoords.rbegin()[2].first << " , " << s_PathCoords.rbegin()[2].second;
				auto it = std::prev(s_PathCoords.end(), 2);
				startNode.m_PosX = it->first;
				startNode.m_PosY = it->second;
				std::cout << "***************you are trying to place to obstacle node\n";

			}
			map.ResetPath();
			startNode.m_Mark = 'S';
			map.Add(startNode);
			movingStartNode = false;
			std::cout << "clearing s_pathcoords \n";
			s_PathCoords.clear();

		}

		if (movingEndNode)
		{
			if (!map.GetNode(mousePosX, mousePosY).m_IsObstacle)
			{
				endNode.m_PosX = mousePosX;
				endNode.m_PosY = mousePosY;
			}
			else
			{
				std::cout << "***************you are trying to place to obstacle node\n";
				//std::cout << s_PathCoords.rbegin()[2].first << " , " << s_PathCoords.rbegin()[2].second;
				auto it = std::prev(s_PathCoords.end(), 2);

				endNode.m_PosX = it->first;
				endNode.m_PosY = it->second;
			}
			
			map.ResetPath();
			endNode.m_Mark = 'E';
			map.Add(endNode);
			s_PathCoords.clear();
			movingEndNode = false;
		}

		m_Path.BeginPathFinding(startNode, endNode);
		dragging = false;
	}
	DrawObstaclesByMouseInput(movingStartNode, movingEndNode);
}

void ApplicationLayer::OnButtonPressedEvent(Timestep ts)
{
	auto& app = Application::Get();
	auto& window = app.GetWindow();
	auto& imGuiWindow = app.GetImGuiWindow();

	if (imGuiWindow.IsDrawMazeButtonPressed())
	{
		map.ResetPath();
		map.ResetObstacles();
		m_Path.ClearAllSet();
		m_Maze.BeginMaze(startNode);
		m_BeginDrawMaze = true;
	}

	if (imGuiWindow.IsFindPathButtonPressed())
	{
		int8_t selectedIndex = imGuiWindow.GetSelectedItemFromDropDown();

		switch (selectedIndex)
		{
		case -1:
			std::cout << "No algorithm selected\n";
			break;
		case 0:
			std::cout << "A Star\n";
			m_Path.BeginPathFinding(startNode, endNode);
			m_BeginPathFinding = true;
			break;
		case 1:
			std::cout << "Dijkstra selected\n";
			break;
		case 2:
			std::cout << "Greedy Best-first\n";
			break;
		case 3:
			std::cout << "Breadth-first\n";
			break;
		case 4:
			std::cout << "Depth-first\n";
			break;
		}
	}

	if (imGuiWindow.IsClearMapButtonPressed())
	{
		std::cout << "Clear map\n";
		map.ResetPath();
		map.ResetObstacles();
		m_Path.ClearAllSet();
		startNode.m_Mark = 'S';
		map.Add(startNode);
		endNode.m_Mark = 'E';
		map.Add(endNode);
	}
}

void ApplicationLayer::OnKeyPressedEvent(Timestep ts)
{
}

void ApplicationLayer::DrawPath(sf::RenderWindow& window)
{
	const auto& openSet = m_Path.GetOpenSet();
	const auto& closedSet = m_Path.GetClosedSet();
	const auto& pathSet = m_Path.GetPathSet();

	const auto& mazeVisited = m_Maze.GetVisited();

	for (const auto& node : openSet)
	{
		DrawNode(window, node, sf::Color::Green);
	}

	for (const auto& node : closedSet)
	{
		DrawNode(window, node, sf::Color::Red);
	}

	for (const auto& node : pathSet)
	{
		DrawNode(window, node, sf::Color::Blue);
	}

	for (const auto& node : mazeVisited)
	{
		//CarvePath(window, node);
	}

	if (!mazeVisited.empty())
		DrawNode(window, mazeVisited.back(), sf::Color::Green);
}

void ApplicationLayer::Render(Timestep ts)
{
	auto& app = Application::Get();
	auto& window = app.GetWindow();

	DrawGrid(window);

	DrawNode(window, startNode, sf::Color::Red);
	DrawNode(window, endNode, sf::Color::Green);

	DrawPath(window);

	Sprite_Arrow.setPosition((startNode.m_PosX * Map::NodeCellSize) + 10.f, (startNode.m_PosY * Map::NodeCellSize) + 10.f);
	Sprite_LocationPin.setPosition((endNode.m_PosX * Map::NodeCellSize) + 10.f, (endNode.m_PosY * Map::NodeCellSize) + 10.f);
	window.draw(Sprite_Arrow);
	window.draw(Sprite_LocationPin);

	DrawObstacles(window);

	int x = (int)(GetMousePos(window).x - 10) / Map::NodeCellSize;
	int y = (int)(GetMousePos(window).y - 10) / Map::NodeCellSize;
	if (movingStartNode)
	{
		if (map.GetNode(x, y).m_IsObstacle)
		{
			DrawNodeMarker(window, x, y, sf::Color::Black);
			return;
		}
		DrawNodeMarker(window, x, y, sf::Color::Red);
	}

	if (movingEndNode)
	{
		DrawNodeMarker(window, x, y, sf::Color::Green);
	}
}

void ApplicationLayer::Update(Timestep ts)
{
	auto& app = Application::Get();
	auto& window = app.GetWindow();
	auto& imGuiWindow = app.GetImGuiWindow();
}

void ApplicationLayer::DrawObstaclesByMouseInput(bool movingStartNode, bool movingEndNode)
{
	auto& app = Application::Get();
	auto& window = app.GetWindow();

	//printf("Mouse: %d, %d\n", GetMousePos(window).x, GetMousePos(window).y);

	int x = (int)(GetMousePos(window).x - 10) / Map::NodeCellSize;
	int y = (int)(GetMousePos(window).y - 10) / Map::NodeCellSize;

	bool startNodeBounds = (x == startNode.m_PosX && y == startNode.m_PosY);
	bool endNodeBounds = (x == endNode.m_PosX && y == endNode.m_PosY);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !movingEndNode && !movingStartNode)
	{
		int x = (GetMousePos(window).x - 10) / Map::NodeCellSize;
		int y = (GetMousePos(window).y - 10) / Map::NodeCellSize; 

		if (!startNodeBounds && !endNodeBounds)
		{
			Node obstacle(x, y, true, false);
			obstacle.m_Mark = 'X';
			map.Add(obstacle);
			DrawNode(window, obstacle, sf::Color(128, 128, 128));
		}
	}
}

void ApplicationLayer::DrawGrid(sf::RenderWindow& window)
{
	sf::Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");
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

void ApplicationLayer::DrawNodeMarker(sf::RenderWindow& window, int x, int y, sf::Color color)
{
	sf::RectangleShape cell(sf::Vector2f(Map::NodeCellSize, Map::NodeCellSize));
	cell.setOutlineColor(color);
	cell.setOutlineThickness(5);

	float cx = (x * Map::NodeCellSize) + 10.f;
	float cy = (y * Map::NodeCellSize) + 10.f;

	cell.setPosition(sf::Vector2f(cx, cy));
	window.draw(cell);
}


void ApplicationLayer::CarvePath(sf::RenderWindow& window, Node node)
{
	sf::RectangleShape line(sf::Vector2f(45.f, 5));
	line.setFillColor(sf::Color::White);
	line.setOutlineColor(sf::Color::White);
	line.setOutlineThickness(3);

	float cx = (node.m_PosX * Map::NodeCellSize) + 10.f;
	float cy = (node.m_PosY * Map::NodeCellSize) + 10.f;
	
	switch (node.GetDir())
	{
	case 0: // left
		//line.setFillColor(sf::Color::Red);
		cx += Map::NodeCellSize;
		line.rotate(90);
		break;

	case 1: // Down
		//line.setFillColor(sf::Color::Red);
		line.rotate(0);
		break;

	case 2: // Right
		//line.setFillColor(sf::Color::Red);
		line.rotate(90);
		break;

	case 3: // Up
		//line.setFillColor(sf::Color::Red); 
		line.rotate(0);
		cy += Map::NodeCellSize;
		break;
	}

	// map.Add(Node(node.m_PosX + ox, node.m_PosY + oy, true));
	// map.Add(Node(node.m_PosX + ox * -1, node.m_PosY + oy * -1, true));
	// map.Add(Node(node.m_PosX, node.m_PosY, false));

	line.setPosition(sf::Vector2f(cx, cy));

	window.draw(line);

	
}


void ApplicationLayer::DrawObstacles(sf::RenderWindow& window)
{
	std::vector<Node> obstacles = map.GetObstacles();

	for (const Node& obstacle : obstacles)
	{
		//DrawNode(window, obstacle, sf::Color(128, 128, 128));
		DrawNode(window, obstacle, sf::Color::Black);

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

void ApplicationLayer::DrawVisitedNodes(sf::RenderWindow& window)
{
	std::vector<Node> visitedNodes = map.GetVisitedNodes();

	for (const Node& v : visitedNodes)
	{
		DrawNode(window, v, sf::Color(255, 177, 88));
	}
}