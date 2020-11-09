#pragma once

#include <SFML/Window/Event.hpp>
#include "Timestep.h"

class Layer
{
public:
	Layer() = default;
	virtual ~Layer() = default;

	virtual void OnInit() {};
	virtual void OnShutDown() {};

	virtual void OnUpdate(Timestep ts) {};
	virtual void OnEvent(sf::Event& event) {};

	virtual void OnButtonPressedEvent(Timestep ts) {};
	virtual void OnKeyPressedEvent(Timestep ts) {};

};