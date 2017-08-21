#pragma once
#include "Behaviour.h"
#include "VehicleAgent.h"

class FuelTooLowQuestion : Behaviour {
public:
	static const float fuel_low_factor;

	FuelTooLowQuestion();

	virtual ~FuelTooLowQuestion();

	virtual Behaviour* clone();

	virtual BehaviourResult update(Agent* agent, float deltaTime);
};