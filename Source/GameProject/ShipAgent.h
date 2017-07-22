#pragma once
#include "stdafx.h"
#include "Agent.h"

class ShipAgent
	: public Agent
{
public:
	ShipAgent();

	ShipAgent(float maxVelocity, float maxForce = def_max_force);

	virtual ~ShipAgent();

	virtual bool onAdd(EntityPtr entity);

	virtual void update(float deltaTime);

	virtual void draw(aie::Renderer2D* renderer) {};

	virtual bool isValidEntity(EntityPtr entity);

};