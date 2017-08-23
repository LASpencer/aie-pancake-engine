#include "stdafx.h"
#include "Wander.h"
#include "imgui.h"
#include "Agent.h"

Wander::Wander() : m_force(std::make_shared<WanderForce>())
{
}

Wander::Wander(float radius, float jitter, float distance) : m_force(std::make_shared<WanderForce>(radius, jitter, distance))
{
}

Wander::Wander(const Wander & other) : m_force(other.m_force)
{
}

Behaviour * Wander::clone()
{
	return new Wander(*this);
}

BehaviourResult Wander::update(Agent * entity, float deltaTime)
{
	entity->addForce(m_force, 1.f);

	return success;
}

void Wander::setRadius(float radius)
{
	m_force->setRadius(radius);
}

void Wander::setJitter(float jitter)
{
	m_force->setJitter(jitter);
}

void Wander::setDistance(float distance)
{
	m_force->setDistance(distance);
}
