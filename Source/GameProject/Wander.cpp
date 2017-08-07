#include "stdafx.h"
#include "Wander.h"
#include "imgui.h"

Wander::Wander() : m_force()
{
}

Wander::Wander(float radius, float jitter, float distance) : m_force(radius, jitter, distance)
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
	entity->addForce(m_force.getForce(entity));
	
	ImGui::Text("Wander behaviour");

	return success;
}

void Wander::setRadius(float radius)
{
	m_force.setRadius(radius);
}

void Wander::setJitter(float jitter)
{
	m_force.setJitter(jitter);
}

void Wander::setDistance(float distance)
{
	m_force.setDistance(distance);
}
