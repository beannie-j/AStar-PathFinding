#include "ImGuiLayer.h"
#include "Application.h"

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
	auto& app = Application::Get();
	auto& window = app.GetWindow();

	ImGui::SFML::Update(window, clock.restart());

	ImGui::Begin("Path Finding");
	ImGui::Button("Start");
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
