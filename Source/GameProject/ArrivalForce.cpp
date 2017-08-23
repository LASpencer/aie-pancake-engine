#include "stdafx.h"
#include "ArrivalForce.h"

const float ArrivalForce::def_radius = 50.f;

ArrivalForce::ArrivalForce() : m_goal(0), m_radius(def_radius)
{
}

ArrivalForce::ArrivalForce(glm::vec2 goal, float radius) : m_goal(goal), m_radius(radius)
{
}

ArrivalForce::ArrivalForce(const ArrivalForce & other) : m_goal(other.m_goal), m_radius(other.m_radius)
{
}

ArrivalForce & ArrivalForce::operator=(const ArrivalForce & other)
{
	m_goal = other.m_goal;
	m_radius = other.m_radius;
	return *this;
}

ArrivalForce::~ArrivalForce()
{
}

void ArrivalForce::setGoal(glm::vec2 goal)
{
	m_goal = goal;
}


glm::vec2 ArrivalForce::getForce(Agent * agent)
{
	return arrivePoint(agent,m_goal, m_radius);
}
