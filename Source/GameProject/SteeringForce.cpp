#include "stdafx.h"
#include "SteeringForce.h"
#include "Entity.h"
#include "Agent.h"


glm::vec2 SteeringForce::seekPoint(Agent * agent, glm::vec2 target)
{
	EntityPtr entity(agent->getEntity());

	glm::vec2 agentPos = agent->getPosition();
	glm::vec2 currentVelocity = agent->getVelocity();

	glm::vec2 displacement = target - agentPos;
	glm::vec2 targetVelocity(0);
	if (displacement != glm::vec2(0)) {
		targetVelocity = glm::normalize(displacement) * agent->getMaxVelocity();
	}
	return targetVelocity - currentVelocity;
}

glm::vec2 SteeringForce::avoidPoint(Agent * agent, glm::vec2 target)
{
	EntityPtr entity(agent->getEntity());

	glm::vec2 agentPos = agent->getPosition();
	glm::vec2 currentVelocity = agent->getVelocity();
	glm::vec2 displacement = target - agentPos;
	glm::vec2 targetVelocity(0);
	if (displacement != glm::vec2(0)) {
		targetVelocity = glm::normalize(agentPos - target) * agent->getMaxVelocity();
	}
	else {
		targetVelocity = glm::vec2(1, 0) * agent->getMaxVelocity();
	}
	return targetVelocity - currentVelocity;
}

glm::vec2 SteeringForce::arrivePoint(Agent * agent, glm::vec2 target, float radius)
{
	EntityPtr entity(agent->getEntity());

	glm::vec2 agentPos = agent->getPosition();
	glm::vec2 currentVelocity = agent->getVelocity();
	glm::vec2 displacement = target - agentPos;
	glm::vec2 targetVelocity(0);
	float targetSpeed = std::min(glm::length(displacement) / radius, 1.f) * agent->getMaxVelocity();
	if (displacement != glm::vec2(0)) {
		 targetVelocity = glm::normalize(target - agentPos) * targetSpeed;
	}
	return targetVelocity - currentVelocity;
}
