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

	bool IsFindPathButtonPressed() { return m_FindPathBtnPressed; }
	bool IsDrawMazeButtonPressed() { return m_DrawMazeBtnPressed; }
	bool IsClearMapButtonPressed() { return m_ClearMapBtnPressed; }

	int8_t GetSelectedItemFromDropDown() { return m_SelectedIndex; }


private:
	bool m_FindPathBtnPressed = false,
		m_DrawMazeBtnPressed = false,
		m_ClearMapBtnPressed = false;

	int8_t m_SelectedIndex = -1;
};