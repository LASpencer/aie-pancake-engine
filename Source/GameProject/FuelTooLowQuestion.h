#pragma once
#include "Behaviour.h"
#include "VehicleAgent.h"

// Returns success if fuel less than some proportion of max fuel
class FuelTooLowQuestion : public Behaviour {
public:
	static const float fuel_low_factor;	// Proportion of maximum considered to be low fuel

	FuelTooLowQuestion();

	virtual ~FuelTooLowQuestion();

	virtual Behaviour* clone();

	virtual BehaviourResult update(Agent* agent, float deltaTime);
};