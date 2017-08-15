#pragma once
#include "Behaviour.h"
#include "VehicleAgent.h"

class AgentIsTankQuestion : public Behaviour {
public:
	AgentIsTankQuestion();

	virtual ~AgentIsTankQuestion();

	virtual Behaviour* clone();

	virtual BehaviourResult update(Agent* agent, float deltaTime);
};