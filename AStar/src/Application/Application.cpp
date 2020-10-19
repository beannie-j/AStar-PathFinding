#include "Application.h"
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

void Application::Init()
{
	s_Window = new sf::RenderWindow(sf::VideoMode(Application::Width, Application::Height), "Path Finder");
}

void Application::Draw()
{
	while (s_Window->isOpen())
	{
		sf::Event event;

		while (s_Window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				s_Window->close();



		}

		
		s_Window->clear(sf::Color::Black);
		s_Window->display();
	}
}

void Application::Run()
{
	Draw();
}

void Application::ShutDown()
{
	//delete s_Application;
	//delete s_Window;
}
