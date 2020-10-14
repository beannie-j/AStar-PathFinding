#pragma once
#include "Node.h"

#include <array>

class Map
{
public:
	static constexpr int GridWidth = 20;
	static constexpr int GridHeight = 10;

	using NodeGrid = std::array<std::array<Node, GridHeight>, GridWidth>;

	NodeGrid grid;

	void Init();
	void Draw();
	void Add(Node node);

	static Map& Get();

	NodeGrid& GetGrid();

	Map();
	~Map();
};

