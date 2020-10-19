#pragma once
#include "Layer.h"

class ApplicationLayer : public Layer
{
public:
	virtual void OnInit() override;
	virtual void OnShutDown() override;

	virtual void OnUpdate() override;
	virtual void OnEvent(sf::Event& event) override;

private:

};

