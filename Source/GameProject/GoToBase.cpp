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
		// Find own base position
		Team agentTeam = tank->getTeam();
		EntityPtr base = agent->getEntity().lock()->getApp()->getBase(agentTeam);
		glm::vec2 basePosition(base->getPosition()->getGlobalTransform()[2]);
		// Pathfind
		bool pathFound = agent->setGoal(basePosition);
		if (pathFound) {
			// Follow path, avoiding getting to close to others
			tank->avoidFriends(0.05f);
			agent->followPath();
			return success;
		} else {
			return failure;
		}
	}
}
