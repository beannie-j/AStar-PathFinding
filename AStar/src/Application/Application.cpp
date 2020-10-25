#include "Application.h"
#include "ApplicationLayer.h"

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
	isPathFound = false;
}

void Application::Render()
{
	while (s_Window->isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		Timestep timestep = time - m_LastFrameTime;
		m_LastFrameTime = time;

		sf::Event event;

		while (s_Window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				s_Window->close();
			
			s_CurrentLayer->OnEvent(event);
		}

		s_Window->clear(sf::Color::Black);
		s_CurrentLayer->OnUpdate(timestep);
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
	//delete s_Application;
	//delete s_Window;
}
