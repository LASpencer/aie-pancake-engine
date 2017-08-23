#pragma once
#include "Behaviour.h"
#include "VehicleAgent.h"

// Follow path leading to base
class GoToBase : public Behaviour {
public:
	GoToBase();

	virtual ~GoToBase();

	virtual Behaviour* clone();

	virtual BehaviourResult update(Agent* agent, float deltaTime);
};