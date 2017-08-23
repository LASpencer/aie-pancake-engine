#include "stdafx.h"
#include "Flocking.h"
#include "GameProjectApp.h"
#include "VehicleAgent.h"


Flocking::Flocking()
{
}


Flocking::~Flocking()
{
}

Behaviour * Flocking::clone()
{
	return new Flocking();
}

BehaviourResult Flocking::update(Agent * agent, float deltaTime)
{
	VehicleAgent* tank = dynamic_cast<VehicleAgent*>(agent);
	if (tank == nullptr) {
		return failure;
	}
	else {
		tank->flock();
		return success;
	}
}
