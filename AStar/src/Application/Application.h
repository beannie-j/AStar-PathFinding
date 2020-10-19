#pragma once
#include <SFML/Graphics.hpp>

#include <Map.h>

struct Grid
{
	inline static int Width = Map::GridWidth;
	inline static int Height = Map::GridHeight;
};

class Application
{
private:
	inline static constexpr unsigned int Width = 100;
	inline static constexpr unsigned int Height = 150;

public:
	Application();
	~Application();

	sf::RenderWindow* s_Window = nullptr;

	Application& Get();
	void Init();
	void Draw();
	void Run();
	void ShutDown();
};

