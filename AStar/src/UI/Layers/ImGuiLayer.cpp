#include "ImGuiLayer.h"
#include "Application.h"
#include <iostream>

void ImGuiLayer::OnInit()
{
	auto& app = Application::Get();
	auto& window = app.GetWindow();
	ImGui::SFML::Init(window);
}

void ImGuiLayer::OnShutDown()
{
}

void ImGuiLayer::OnUpdate(Timestep ts)
{
}

void ImGuiLayer::OnUpdate(sf::Clock clock)
{
	m_FindPathBtnPressed = false, m_DrawMazeBtnPressed = false, m_ClearMapBtnPressed = false;

	float height = Application::Height / 4;
	float width = Application::Width / 3;
	auto& app = Application::Get();
	auto& window = app.GetWindow();

	ImGui::SFML::Update(window, clock.restart());

	ImGui::Begin("Guide");

	ImGui::SetWindowPos("Guide", ImVec2(1480, 200));
	ImGui::SetWindowSize("Guide", ImVec2(width, height));
	ImGui::SetWindowFontScale(2.0f);

	ImGui::Text("Click on below buttons to start");
	ImGui::Text("drawing!");

	ImGui::Dummy(ImVec2(0.0f, 20.0f));

	ImGuiComboFlags flags = ImGuiComboFlags_NoArrowButton;

	const char* items[] = { "A Star", "Dijkstra", "Greedy Best-first", "Breadth-first", "Depth-first" };
	static const char* currentItem = "Select algorithm";

	if (ImGui::BeginCombo("##custom combo", currentItem, ImGuiComboFlags_NoArrowButton))
	{
		for (int n = 0; n < IM_ARRAYSIZE(items); n++)
		{
			bool is_selected = (currentItem == items[n]);
			if (ImGui::Selectable(items[n], is_selected))
			{
				currentItem = items[n];
				m_SelectedIndex = n;
				std::cout << "[Selected] : " << n << " : "<< currentItem << std::endl;
			}
	
			if (is_selected)
			{
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}

	ImGui::Dummy(ImVec2(0.0f, 20.0f));

	if (ImGui::Button("Find Path"))
	{
		m_FindPathBtnPressed = !m_FindPathBtnPressed;
	}
	ImGui::Dummy(ImVec2(0.0f, 20.0f));

	if (ImGui::Button("Clear Map"))
	{
		m_ClearMapBtnPressed = !m_ClearMapBtnPressed;
	}
	ImGui::Dummy(ImVec2(0.0f, 20.0f));

	if (ImGui::Button("Draw Maze"))
	{
		m_DrawMazeBtnPressed = !m_DrawMazeBtnPressed;
	}
	ImGui::End();
}

void ImGuiLayer::Render()
{
	auto& app = Application::Get();
	auto& window = app.GetWindow();
	ImGui::SFML::Render(window);
}

void ImGuiLayer::OnEvent(sf::Event& event)
{
	ImGui::SFML::ProcessEvent(event);
}
