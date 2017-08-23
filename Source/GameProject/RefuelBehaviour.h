#pragma once
#include "Behaviour.h"
#include "VehicleAgent.h"

// Tank refuels until it's full
class RefuelBehaviour : public Behaviour {
public:
	static const float refuel_rate;

	RefuelBehaviour();
	virtual ~RefuelBehaviour();

	virtual Behaviour* clone();

	// Keeps running until tank filled, then returns success
	virtual BehaviourResult update(Agent* agent, float deltaTime);
};