#include "stdafx.h"
#include "PursueForce.h"

const float PursueForce::def_target_size = 30.f;

PursueForce::PursueForce()
{
}


PursueForce::PursueForce(const PursueForce & other)
{
}

PursueForce & PursueForce::operator=(const PursueForce & other)
{
	return *this;
}

PursueForce::~PursueForce()
{
}


glm::vec2 PursueForce::getForce(Agent * agent)
{
	AgentPtr target = agent->getTarget();
	glm::vec2 relativeVelocity = agent->getVelocity() - target->getVelocity();
	glm::vec2 displacement = target->getPosition() - agent->getPosition();
	glm::vec2 targetVelocity(0);

	if (glm::length(displacement) > def_target_size) {
		targetVelocity = std::max(agent->getMaxVelocity(), glm::dot(relativeVelocity, displacement)) * glm::normalize(displacement);
	}

	return targetVelocity - relativeVelocity;
}
