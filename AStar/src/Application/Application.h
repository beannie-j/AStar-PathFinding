#pragma once
#include <SFML/Graphics.hpp>

#include "Map.h"
#include "Layer.h"
#include "Timestep.h"
#include "ImGuiLayer.h"

#include <imgui.h>

struct Grid
{
	inline static int Width = Map::GridWidth;
	inline static int Height = Map::GridHeight;
};

class Application
{
private:
	sf::Clock clock;
	sf::Time time;
	float m_LastFrameTime = 0.0f;
	bool m_Running = false;


public:
	inline static constexpr uint32_t Width = 2000;
	inline static constexpr uint32_t Height = 1500;

	Application();
	~Application();

	sf::RenderWindow* s_Window = nullptr;
	Layer* s_CurrentLayer = nullptr;

	ImGuiLayer* s_ImGuiWindow = nullptr;

	static Application& Get();
	sf::RenderWindow& GetWindow();

	ImGuiLayer& GetImGuiWindow() { return *s_ImGuiWindow; }


	void SetLayer(Layer* layer);
	void Init();
	void Render();
	void Run();
	void ShutDown();
};

