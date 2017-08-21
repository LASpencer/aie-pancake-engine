#include "stdafx.h"
#include "DeathBehaviour.h"
#include "imgui.h"
#include "Agent.h"
#include "VehicleAgent.h"

DeathBehaviour::DeathBehaviour()
{
}

DeathBehaviour::~DeathBehaviour()
{
}

Behaviour * DeathBehaviour::clone()
{
	return new DeathBehaviour(*this);
}

BehaviourResult DeathBehaviour::update(Agent * agent, float deltaTime)
{
	// Respawn if dead for long enough
	
	if (agent->getTimer(Agent::dead).getTime() > 3.f) {
		VehicleAgent* tank = dynamic_cast<VehicleAgent*>(agent);
		if (tank != nullptr) {
			tank->respawn();
		}
	}
	return success;
}
