#include "stdafx.h"
#include "SeekForce.h"

SeekForce::SeekForce() : m_target(nullptr)
{
}

SeekForce::SeekForce(TargetPtr target) : m_target(target)
{
}

SeekForce::SeekForce(const SeekForce & other) : m_target(other.m_target)
{
}

SeekForce & SeekForce::operator=(const SeekForce & other)
{
	m_target = other.m_target;
	return *this;
}

SeekForce::~SeekForce()
{
}

void SeekForce::setTarget(TargetPtr target)
{
	m_target = target;
}

glm::vec2 SeekForce::getForce(Agent * agent)
{
	return seekPoint(agent, m_target->getPosition());
}
