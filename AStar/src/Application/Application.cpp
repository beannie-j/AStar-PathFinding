#include "Application.h"
#include "ApplicationLayer.h"

#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "ImGuiLayer.h"


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
	s_ImGuiWindow = new ImGuiLayer();
	s_ImGuiWindow->OnInit();
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
			s_ImGuiWindow->OnEvent(event);

			if (event.type == sf::Event::Closed)
			{
				s_Window->close();
				ShutDown();
			}
			s_CurrentLayer->OnEvent(event);
		}

		s_ImGuiWindow->OnUpdate(deltaClock);

		s_Window->clear(sf::Color::Black);
		s_CurrentLayer->OnUpdate(timestep);
		s_CurrentLayer->OnButtonPressedEvent(timestep);
		s_CurrentLayer->OnKeyPressedEvent(timestep);
		
		s_ImGuiWindow->Render();
		
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
