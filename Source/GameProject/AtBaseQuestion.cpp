#include "stdafx.h"
#include "AtBaseQuestion.h"
#include "GameProjectApp.h"

const float AtBaseQuestion::base_size = 50.f;

AtBaseQuestion::AtBaseQuestion()
{
}

AtBaseQuestion::~AtBaseQuestion()
{
}

Behaviour * AtBaseQuestion::clone()
{
	return new AtBaseQuestion();
}

BehaviourResult AtBaseQuestion::update(Agent * agent, float deltaTime)
{
	VehicleAgent* tank = dynamic_cast<VehicleAgent*>(agent);
	if (tank == nullptr) {
		return failure;
	}
	else {
		Team agentTeam = tank->getTeam();
		EntityPtr base = agent->getEntity().lock()->getApp()->getBase(agentTeam);
		glm::vec2 basePosition(base->getPosition()->getGlobalTransform()[2]);
		glm::vec2 displacement = basePosition - agent->getPosition();
		if (glm::dot(displacement, displacement) < base_size * base_size) {
			return success;
		} else {
			return failure;
		}
	}
}
