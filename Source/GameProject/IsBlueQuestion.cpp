#include "stdafx.h"
#include "IsBlueQuestion.h"

IsBlueQuestion::IsBlueQuestion()
{
}

IsBlueQuestion::~IsBlueQuestion()
{
}

Behaviour * IsBlueQuestion::clone()
{
	return new IsBlueQuestion();
}

BehaviourResult IsBlueQuestion::update(Agent * agent, float deltaTime)
{
	VehicleAgent* tank = dynamic_cast<VehicleAgent*>(agent);
	if (tank != nullptr && tank->getTeam() == blue) {
		return success;
	}
	else {
		return failure;
	}
}
