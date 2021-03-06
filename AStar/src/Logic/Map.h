#pragma once
#include "Node.h"
#include <vector>

class Map
{
public:
	static constexpr uint16_t GridWidth = 29;
	static constexpr uint16_t GridHeight = 30;
	static constexpr float NodeCellSize = 50.0f;

	Node* currentNode = nullptr;

	using NodeGrid = Node[GridWidth * GridHeight];
	NodeGrid grid;

	int Size();
	void Init();
	void Draw();
	void Add(const Node& node);

	static Map& Get();

	NodeGrid& GetGrid();
	Node& GetNode(int x, int y);

	std::vector<Node> GetObstacles();
	std::vector<Node> GetPathNodes();
	std::vector<Node> GetVisitedNodes();
	std::vector<Node> GetWalls();


	void ResetObstacles();
	void ResetPath();

	Map();
	~Map();
};

