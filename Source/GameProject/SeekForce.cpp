#include "stdafx.h"
#include "SeekForce.h"

SeekForce::SeekForce() : m_target(nullptr)
{
}

SeekForce::SeekForce(Target * target) : m_target(target->clone())
{
}

SeekForce::SeekForce(const SeekForce & other) : m_target(other.m_target->clone())
{
}

SeekForce & SeekForce::operator=(const SeekForce & other)
{
	delete m_target;
	m_target = other.m_target->clone();
	return *this;
}

SeekForce::~SeekForce()
{
	delete m_target;
}

void SeekForce::setTarget(Target * target)
{
	delete m_target;
	m_target = target->clone();
}

glm::vec2 SeekForce::getForce(Agent * agent)
{
	return seekPoint(agent, m_target->getPosition());
}
