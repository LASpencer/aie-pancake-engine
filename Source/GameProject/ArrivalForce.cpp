#include "stdafx.h"
#include "ArrivalForce.h"

const float ArrivalForce::def_radius = 50.f;

ArrivalForce::ArrivalForce() : m_target(nullptr), m_radius(def_radius)
{
}

ArrivalForce::ArrivalForce(Target * target, float radius) : m_target(target->clone()), m_radius(radius)
{
}

ArrivalForce::ArrivalForce(const ArrivalForce & other) : m_target(other.m_target->clone())
{
}

ArrivalForce & ArrivalForce::operator=(const ArrivalForce & other)
{
	delete m_target;
	m_target = other.m_target->clone();
	return *this;
}

ArrivalForce::~ArrivalForce()
{
	delete m_target;
}

void ArrivalForce::setTarget(Target * target)
{
	delete m_target;
	m_target = target->clone();
}

glm::vec2 ArrivalForce::getForce(Agent * agent)
{
	return arrivePoint(agent, m_target->getPosition(), m_radius);
}
