#pragma once
#include <SFML/Graphics.hpp>

#include "Map.h"
#include "Layer.h"

struct Grid
{
	inline static int Width = Map::GridWidth;
	inline static int Height = Map::GridHeight;
};

class Application
{
private:
	

public:
	inline static constexpr unsigned int Width = 1500;
	inline static constexpr unsigned int Height = 1500;

	Application();
	~Application();

	bool isPathFound;
	sf::RenderWindow* s_Window = nullptr;
	Layer* s_CurrentLayer = nullptr;

	static Application& Get();
	sf::RenderWindow& GetWindow();

	void SetLayer(Layer* layer);
	void Init();
	void Draw();
	void Run();
	void ShutDown();
};

