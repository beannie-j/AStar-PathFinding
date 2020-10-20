#pragma once
#include "Node.h"
#include <vector>

class Map
{
public:
	static constexpr int GridWidth = 20;
	static constexpr int GridHeight = 27;
	static constexpr float NodeCellSize = 50.0f;

	Node* currentNode = nullptr;

	using NodeGrid = Node[GridWidth * GridHeight];
	NodeGrid grid;

	void Init();
	void Draw();
	void Add(Node& node);

	static Map& Get();

	NodeGrid& GetGrid();
	Node& GetNode(int x, int y);

	std::vector<Node> GetObstacles();
	std::vector<Node> GetPathNodes();

	Map();
	~Map();
};

