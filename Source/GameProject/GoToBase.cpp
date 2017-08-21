#include "stdafx.h"
#include "GoToBase.h"
#include "GameProjectApp.h"

GoToBase::GoToBase()
{
}

GoToBase::~GoToBase()
{
}

Behaviour * GoToBase::clone()
{
	return new GoToBase();
}

BehaviourResult GoToBase::update(Agent * agent, float deltaTime)
{
	VehicleAgent* tank = dynamic_cast<VehicleAgent*>(agent);
	if (tank == nullptr) {
		return failure;
	}
	else {
		//TODO if this is slow, have some way to check if path is already valid, and if so use it
		Team agentTeam = tank->getTeam();
		EntityPtr base = agent->getEntity().lock()->getApp()->getBase(agentTeam);
		glm::vec2 basePosition(base->getPosition()->getGlobalTransform()[2]);
		bool pathFound = agent->setGoal(basePosition);
		if (pathFound) {
			agent->followPath();
			return success;
		} else {
			return failure;
		}
	}
}
