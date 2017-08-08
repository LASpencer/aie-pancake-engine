#pragma once
#include "stdafx.h"
#include "Agent.h"

class SimpleAgent
	: public Agent
{
public:
	SimpleAgent();

	SimpleAgent(float maxVelocity, float maxForce = def_max_force);

	virtual ~SimpleAgent();

	virtual void update(float deltaTime);

	virtual void draw(aie::Renderer2D* renderer);

};