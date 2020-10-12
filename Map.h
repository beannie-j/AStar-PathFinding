#pragma once
#include "Node.h"

#include <array>

class Map
{
public:
	static constexpr int GridWidth = 20;
	static constexpr int GridHeight = 10;

	std::array<std::array<Node, GridHeight>, GridWidth> grid;

	void Init();
	void Draw();
	void Add(Node node);

	static Map& Get();

	auto& GetGrid();

	Map();
	~Map();
};
