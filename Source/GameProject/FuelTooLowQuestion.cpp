#include "stdafx.h"
#include "FuelTooLowQuestion.h"

const float FuelTooLowQuestion::fuel_low_factor = 0.2f;

FuelTooLowQuestion::FuelTooLowQuestion()
{
}

FuelTooLowQuestion::~FuelTooLowQuestion()
{
}

Behaviour * FuelTooLowQuestion::clone()
{
	return new FuelTooLowQuestion();
}

BehaviourResult FuelTooLowQuestion::update(Agent * agent, float deltaTime)
{
	VehicleAgent* tank = dynamic_cast<VehicleAgent*>(agent);
	if (tank == nullptr) {
		return failure;
	} else if(tank->getFuel() < tank->getMaxFuel() * fuel_low_factor){
		return success;
	} else {
		return failure;
	}
}
