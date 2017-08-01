#include "stdafx.h"
#include "DrunkenModifier.h"
#include "Entity.h"
#include "Agent.h"

DrunkenModifier::DrunkenModifier() : m_time(0.f)
{
}

DrunkenModifier::~DrunkenModifier()
{
}

BehaviourResult DrunkenModifier::update(Agent* agent, float deltaTime)
{
	m_time += deltaTime;

	float magnitude = agent->getMaxForce() * 0.5f;

	glm::vec2 force(cosf(m_time), sinf(m_time));
	force *= magnitude;

	agent->addForce(force);

	return success;
}
