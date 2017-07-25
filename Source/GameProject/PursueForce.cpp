#include "stdafx.h"
#include "PursueForce.h"

const float PursueForce::def_target_size = 20.f;

PursueForce::PursueForce() : m_target(nullptr)
{
}

PursueForce::PursueForce(Target * target) : m_target(target->clone())
{
}

PursueForce::PursueForce(const PursueForce & other) : m_target(other.m_target->clone())
{
}

PursueForce & PursueForce::operator=(const PursueForce & other)
{
	delete m_target;
	m_target = other.m_target->clone();
	return *this;
}

PursueForce::~PursueForce()
{
	delete m_target;
}

void PursueForce::setTarget(Target * target)
{
	delete m_target;
	m_target = target->clone();
}

glm::vec2 PursueForce::getForce(Agent * agent)
{
	glm::vec2 relativeVelocity = agent->getVelocity() - m_target->getVelocity();
	glm::vec2 displacement = m_target->getPosition() - agent->getPosition();
	glm::vec2 targetVelocity(0);

	if (glm::length(displacement) > def_target_size) {
		targetVelocity = std::max(agent->getMaxVelocity(), glm::dot(relativeVelocity, displacement)) * glm::normalize(displacement);
	}

	return targetVelocity - relativeVelocity;
}
