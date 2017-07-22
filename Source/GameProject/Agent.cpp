#include "stdafx.h"
#include "Agent.h"
#include "Entity.h"

const float Agent::def_max_velocity = 1000.f;
const float Agent::def_max_force = 1000.f;

Agent::Agent() : Component(), m_maxVelocity(def_max_velocity), m_maxForce(def_max_force)
{
}

Agent::Agent(float maxVelocity, float maxForce) : Component(), m_maxVelocity(maxVelocity), m_maxForce(maxForce)
{
}

Agent::~Agent()
{
}

Agent::Identifier Agent::getID()
{
	return agent;
}

bool Agent::isValidEntity(EntityPtr entity)
{
	// Entity must have a body
	return (entity->getComponentMask() & Component::body);
}
