#include "stdafx.h"
#include "SeekForce.h"

SeekForce::SeekForce() : m_goal(0)
{
}

SeekForce::SeekForce(glm::vec2 goal) : m_goal(goal)
{
}

SeekForce::SeekForce(const SeekForce & other) : m_goal(other.m_goal)
{
}

SeekForce & SeekForce::operator=(const SeekForce & other)
{
	m_goal = other.m_goal;
	return *this;
}

SeekForce::~SeekForce()
{
}

void SeekForce::setGoal(glm::vec2 goal)
{
	m_goal = goal;
}


glm::vec2 SeekForce::getForce(Agent * agent)
{
	return seekPoint(agent, m_goal);
}
