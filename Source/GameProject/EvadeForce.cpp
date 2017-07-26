#include "stdafx.h"
#include "EvadeForce.h"

const float EvadeForce::def_target_size = 20.f;

EvadeForce::EvadeForce()
{
}

EvadeForce::EvadeForce(TargetPtr target) : m_target(target)
{
}

EvadeForce::EvadeForce(const EvadeForce & other) : m_target(other.m_target)
{
}

EvadeForce & EvadeForce::operator=(const EvadeForce & other)
{
	m_target = other.m_target;
	return *this;
}

EvadeForce::~EvadeForce()
{
}

void EvadeForce::setTarget(TargetPtr target)
{
	m_target = target;
}

glm::vec2 EvadeForce::getForce(Agent * agent)
{
	glm::vec2 relativeVelocity = agent->getVelocity() - m_target->getVelocity();
	glm::vec2 displacement = m_target->getPosition() - agent->getPosition();
	float closingSpeed = glm::dot(relativeVelocity, displacement);

	/*float collisionTime = INFINITY;
	if (closingSpeed > 0.f) {
		collisionTime = glm::length(displacement) / closingSpeed;
	}
	glm::vec2 closingVelocity = closingSpeed * glm::normalize(displacement);
	glm::vec2 lateralVelocity = relativeVelocity - closingVelocity;*/
	
	glm::vec2 targetVelocity = std::min(-agent->getMaxVelocity(), closingSpeed) * glm::normalize(displacement);
	return targetVelocity - relativeVelocity;
}
