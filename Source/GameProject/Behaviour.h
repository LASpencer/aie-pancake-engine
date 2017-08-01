#pragma once
#include "stdafx.h"

//TODO behaviours should be passed agent instead of entity

class Agent;

class Behaviour;
typedef std::shared_ptr<Behaviour> BehaviourPtr;

class Behaviour
{
public:
	Behaviour() {};
	virtual ~Behaviour() {};

	virtual Behaviour* clone() = 0;

	virtual bool update(Agent* agent, float deltaTime) = 0;
};
