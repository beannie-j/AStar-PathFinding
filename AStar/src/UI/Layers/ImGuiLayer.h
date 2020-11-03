#pragma once
#include "Layer.h"
#include "Timestep.h"
#include "ImGuiLayer.h"

#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

class ImGuiLayer : public Layer
{
public:
	virtual void OnInit() override;
	virtual void OnShutDown() override;

	virtual void OnUpdate(Timestep ts) override;
	virtual void OnEvent(sf::Event& event) override;

	void OnUpdate(sf::Clock clock);
	void Render();

private:

};