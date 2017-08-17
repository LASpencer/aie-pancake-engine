#pragma once
#include "Behaviour.h"
#include "VehicleAgent.h"

// Returns success if agent is vehicle and is not alive
class IsDeadQuestion : public Behaviour {
public:
	IsDeadQuestion();

	virtual ~IsDeadQuestion();

	virtual Behaviour* clone();

	virtual BehaviourResult update(Agent* agent, float deltaTime);
};