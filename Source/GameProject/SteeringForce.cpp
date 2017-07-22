#include "stdafx.h"
#include "SteeringForce.h"
#include "Entity.h"
#include "Body.h"

glm::vec2 SteeringForce::seekPoint(Agent * agent, glm::vec2 target)
{
	EntityPtr entity(agent->getEntity());
	std::shared_ptr<Body> body = std::dynamic_pointer_cast<Body>(entity->getComponent(Component::body));

	glm::vec2 agentPos = glm::vec2(entity->getPosition()->getGlobalTransform()[2]);
	glm::vec2 currentVelocity = body->getVelocity();

	glm::vec2 targetVelocity = glm::normalize(target - agentPos) * agent->getMaxVelocity();

	return targetVelocity - currentVelocity;
}

glm::vec2 SteeringForce::avoidPoint(Agent * agent, glm::vec2 target)
{
	EntityPtr entity(agent->getEntity());
	std::shared_ptr<Body> body = std::dynamic_pointer_cast<Body>(entity->getComponent(Component::body));

	glm::vec2 agentPos = glm::vec2(entity->getPosition()->getGlobalTransform()[2]);
	glm::vec2 currentVelocity = body->getVelocity();

	glm::vec2 targetVelocity = glm::normalize(agentPos - target) * agent->getMaxVelocity();

	return targetVelocity - currentVelocity;
}

glm::vec2 SteeringForce::arrivePoint(Agent * agent, glm::vec2 target, float radius)
{
	EntityPtr entity(agent->getEntity());
	std::shared_ptr<Body> body = std::dynamic_pointer_cast<Body>(entity->getComponent(Component::body));

	glm::vec2 agentPos = glm::vec2(entity->getPosition()->getGlobalTransform()[2]);
	glm::vec2 currentVelocity = body->getVelocity();
	float targetSpeed = std::min(glm::length(target - agentPos) / radius, agent->getMaxVelocity());
	glm::vec2 targetVelocity = glm::normalize(target - agentPos) * targetSpeed;

	return targetVelocity - currentVelocity;
}
