#include "stdafx.h"
#include "Body.h"
#include "Entity.h"

Body::~Body()
{
}

void Body::setVelocity(glm::vec2 velocity)
{
	m_velocity = velocity;
}

void Body::applyDeltaV(glm::vec2 deltaV)
{
	m_velocity += deltaV;
}

void Body::applyImpulse(glm::vec2 impulse)
{
	m_velocity += (impulse * m_invmass);
}

void Body::setDrag(float drag)
{
	m_drag = abs(drag);
}

void Body::setMass(float mass)
{
	if (mass == 0.0f || std::isinf(mass)) {
		m_invmass = 0.0f;
	}
	else {
		m_invmass = 1.0f / mass;
	}
}

float Body::getInvMass()
{
	return m_invmass;
}

void Body::update(float deltaTime)
{
	EntityPtr entity(m_entity);

	glm::vec2 displacement(0);

	displacement += 0.5f * deltaTime * m_velocity;

	// Apply drag to velocity
	glm::vec2 drag = deltaTime * m_invmass * m_drag * -m_velocity;
	if (glm::dot(drag, drag) > glm::dot(m_velocity, m_velocity)) {
		m_velocity = glm::vec2(0);
	}
	else {
		m_velocity += drag;
	}

	m_velocity += deltaTime * m_invmass * m_force;

	displacement += 0.5f * deltaTime * m_velocity;

	entity->getPosition()->globalTranslate(displacement);
}
