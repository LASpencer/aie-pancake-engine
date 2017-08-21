#include "stdafx.h"
#include "IsDeadQuestion.h"

IsDeadQuestion::IsDeadQuestion()
{
}

IsDeadQuestion::~IsDeadQuestion()
{
}

Behaviour * IsDeadQuestion::clone()
{
	return new IsDeadQuestion();
}

BehaviourResult IsDeadQuestion::update(Agent * agent, float deltaTime)
{
	VehicleAgent* vehicle = dynamic_cast<VehicleAgent*>(agent);
	if (vehicle != nullptr && vehicle->isAlive()) {
		return failure;
	}
	else {
		return success;
	}
}
