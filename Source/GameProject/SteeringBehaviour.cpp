#include "stdafx.h"
#include "SteeringBehaviour.h"

SteeringBehaviour::SteeringBehaviour()
{
}

SteeringBehaviour::SteeringBehaviour(SteeringForcePtr force) : m_force(force)
{
}

SteeringBehaviour::~SteeringBehaviour()
{
}

BehaviourResult SteeringBehaviour::update(Agent * entity, float deltaTime)
{
	entity->addForce(m_force->getForce(entity));

	return success;
}
