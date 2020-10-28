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
	s_Window->setKeyRepeatEnabled(false);
	m_Running = true;
}

void Application::Render()
{
	while (m_Running)
	{
		float time = clock.getElapsedTime().asSeconds();
		Timestep timestep = time - m_LastFrameTime;
		m_LastFrameTime = time;

		sf::Event event;

		while (s_Window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				s_Window->close();
				ShutDown();
			}
			
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
	// why exception here?
	m_Running = false;
	//delete s_Application;
	//delete s_Window;
}
