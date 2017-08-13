#include "stdafx.h"
#include "SteeringBehaviour.h"
#include "Agent.h"

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

BehaviourResult SteeringBehaviour::update(Agent * agent, float deltaTime)
{
	agent->addForce(m_force, 1.f);

	return success;
}

void SteeringBehaviour::draw(Agent * agent, aie::Renderer2D * renderer)
{
	m_force->draw(agent, renderer);
}
