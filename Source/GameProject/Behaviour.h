#pragma once
#include "stdafx.h"
#include "Renderer2D.h"

class Agent;

class Behaviour;
typedef std::shared_ptr<Behaviour> BehaviourPtr;

enum BehaviourResult {
	failure,
	success,
	running
};

// Base class for behaviours
class Behaviour
{
public:
	Behaviour() {};
	virtual ~Behaviour() {};

	virtual Behaviour* clone() = 0;

	virtual BehaviourResult update(Agent* agent, float deltaTime) = 0;

	virtual void draw(Agent* agent, aie::Renderer2D* renderer) {};
};
