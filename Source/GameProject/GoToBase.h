#pragma once
#include "Behaviour.h"
#include "VehicleAgent.h"

class GoToBase : Behaviour {
public:
	GoToBase();

	virtual ~GoToBase();

	virtual Behaviour* clone();

	virtual BehaviourResult update(Agent* agent, float deltaTime);
};