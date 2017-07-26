#include "stdafx.h"
#include "ArrivalForce.h"

const float ArrivalForce::def_radius = 50.f;

ArrivalForce::ArrivalForce() : m_target(nullptr), m_radius(def_radius)
{
}

ArrivalForce::ArrivalForce(TargetPtr target, float radius) : m_target(target), m_radius(radius)
{
}

ArrivalForce::ArrivalForce(const ArrivalForce & other) : m_target(other.m_target)
{
}

ArrivalForce & ArrivalForce::operator=(const ArrivalForce & other)
{
	m_target = other.m_target;
	return *this;
}

ArrivalForce::~ArrivalForce()
{
}

void ArrivalForce::setTarget(TargetPtr target)
{
	m_target = target;
}

glm::vec2 ArrivalForce::getForce(Agent * agent)
{
	return arrivePoint(agent, m_target->getPosition(), m_radius);
}
