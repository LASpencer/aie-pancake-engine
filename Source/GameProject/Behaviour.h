#pragma once
#include "stdafx.h"

//TODO behaviours should be passed agent instead of entity

class Agent;

class Behaviour;
typedef std::shared_ptr<Behaviour> BehaviourPtr;

enum BehaviourResult {
	failure,
	success,
	running
};

class Behaviour
{
public:
	Behaviour() {};
	virtual ~Behaviour() {};

	virtual Behaviour* clone() = 0;

	virtual BehaviourResult update(Agent* agent, float deltaTime) = 0;
};
