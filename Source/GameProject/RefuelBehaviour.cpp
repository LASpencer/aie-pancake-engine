#include "stdafx.h"
#include "RefuelBehaviour.h"

const float RefuelBehaviour::refuel_rate = 20.f;

RefuelBehaviour::RefuelBehaviour()
{
}

RefuelBehaviour::~RefuelBehaviour()
{
}

Behaviour * RefuelBehaviour::clone()
{
	return new RefuelBehaviour();
}

BehaviourResult RefuelBehaviour::update(Agent * agent, float deltaTime)
{
	VehicleAgent* tank = dynamic_cast<VehicleAgent*>(agent);
	if (tank == nullptr) {
		return failure;
	} else if(tank->getFuel() > tank->getMaxFuel() * 0.95f){
		return success;
	} else{
		tank->addFuel(refuel_rate * deltaTime);
		tank->stop();
		return running;
	}
}
