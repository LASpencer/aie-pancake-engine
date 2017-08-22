#pragma once
#include "Behaviour.h"
#include "VehicleAgent.h"

// Returns success if agent is vehicle on blue team
class IsBlueQuestion : public Behaviour {
public:
	IsBlueQuestion();

	virtual ~IsBlueQuestion();

	virtual Behaviour* clone();

	virtual BehaviourResult update(Agent* agent, float deltaTime);
};