#include "Application.h"
#include "ApplicationLayer.h"

#include <imgui.h>
#include <imgui-SFML.h>


#include <iostream>

static Application* s_Application = nullptr;

Application::Application()
{
	s_Application = this;
}

Application::~Application()
{
	ShutDown();
}

Application& Application::Get()
{
	return *s_Application;
}

sf::RenderWindow& Application::GetWindow()
{
	return *s_Window;
}

void Application::SetLayer(Layer* layer)
{
	s_CurrentLayer = layer;
	s_CurrentLayer->OnInit();
}

void Application::Init()
{
	s_Window = new sf::RenderWindow(sf::VideoMode(Application::Width, Application::Height), "Path Finder");
	s_Window->setKeyRepeatEnabled(false);
	s_Window->setVerticalSyncEnabled(true);
	ImGui::SFML::Init(*s_Window);
	m_Running = true;
}

void Application::Render()
{
	sf::Clock deltaClock;
	while (m_Running)
	{
		float time = clock.getElapsedTime().asSeconds();
		Timestep timestep = time - m_LastFrameTime;
		m_LastFrameTime = time;

		sf::Event event;
	
		while (s_Window->pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);
			if (event.type == sf::Event::Closed)
			{
				s_Window->close();
				ShutDown();
			}
			s_CurrentLayer->OnEvent(event);
		}

		ImGui::SFML::Update(*s_Window, deltaClock.restart());

		ImGui::Begin("Hello, world!");
		ImGui::Button("Look at this pretty button");
		ImGui::End();

		s_Window->clear(sf::Color::Black);
		s_CurrentLayer->OnUpdate(timestep);

		ImGui::SFML::Render(*s_Window);
		s_Window->display();
	}
} 

void Application::Run()
{
	SetLayer(new ApplicationLayer());
	Render();
}

void Application::ShutDown()
{
	m_Running = false;
	//delete s_Application;
	//delete s_Window;
}
