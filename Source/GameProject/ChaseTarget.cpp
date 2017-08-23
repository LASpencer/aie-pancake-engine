#include "stdafx.h"
#include "ChaseTarget.h"
#include "Agent.h"
#include "VehicleAgent.h"

ChaseTarget::ChaseTarget()
{
}

ChaseTarget::~ChaseTarget()
{
}

Behaviour * ChaseTarget::clone()
{
	return new ChaseTarget();
}

BehaviourResult ChaseTarget::update(Agent * agent, float deltaTime)
{
	if (agent->pursueTarget()) {
		return success;
	}
	return failure;
}
