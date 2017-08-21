#pragma once
#include "Behaviour.h"
#include "VehicleAgent.h"

class RefuelBehaviour : Behaviour {
public:
	static const float refuel_rate;

	RefuelBehaviour();
	virtual ~RefuelBehaviour();

	virtual Behaviour* clone();

	virtual BehaviourResult update(Agent* agent, float deltaTime);
};