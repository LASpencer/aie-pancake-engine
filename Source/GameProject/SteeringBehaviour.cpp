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

Behaviour * SteeringBehaviour::clone()
{
	return new SteeringBehaviour(*this);
}

BehaviourResult SteeringBehaviour::update(Agent * entity, float deltaTime)
{
	entity->addForce(m_force->getForce(entity));

	return success;
}

void SteeringBehaviour::draw(Agent * agent, aie::Renderer2D * renderer)
{
	m_force->draw(agent, renderer);
}
