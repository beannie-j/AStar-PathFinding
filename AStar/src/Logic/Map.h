#pragma once
#include "Node.h"


class Map
{
public:
	static constexpr int GridWidth = 20;
	static constexpr int GridHeight = 10;

	using NodeGrid = Node[GridWidth * GridHeight];

	NodeGrid grid;

	void Init();
	void Draw();
	void Add(Node& node);

	static Map& Get();

	NodeGrid& GetGrid();

	Node& GetNode(int x, int y);

	Map();
	~Map();
};

