#pragma once
#include "Behaviour.h"
#include "VehicleAgent.h"

// Checks if agent is a tank
class AgentIsTankQuestion : public Behaviour {
public:
	AgentIsTankQuestion();

	virtual ~AgentIsTankQuestion();

	virtual Behaviour* clone();

	virtual BehaviourResult update(Agent* agent, float deltaTime);
};