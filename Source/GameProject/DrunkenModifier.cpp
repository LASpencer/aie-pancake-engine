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

void DrunkenModifier::update(EntityPtr entity, float deltaTime)
{
	m_time += deltaTime;

	std::shared_ptr<Agent> agent = std::dynamic_pointer_cast<Agent>(entity->getComponent(Component::agent));

	float magnitude = agent->getMaxForce() * 0.5f;

	glm::vec2 force(cosf(m_time), sinf(m_time));
	force *= magnitude;

	agent->addForce(force);
}
