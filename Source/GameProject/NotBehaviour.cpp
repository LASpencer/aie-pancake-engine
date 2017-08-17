#include "stdafx.h"
#include "NotBehaviour.h"

NotBehaviour::NotBehaviour()
{
}

NotBehaviour::NotBehaviour(BehaviourPtr behaviour) : m_behaviour(behaviour)
{
}

NotBehaviour::~NotBehaviour()
{
}

Behaviour * NotBehaviour::clone()
{
	return new NotBehaviour(*this);
}

BehaviourResult NotBehaviour::update(Agent * agent, float deltaTime)
{
	switch (m_behaviour->update(agent, deltaTime)) {
	case(success):
		return failure;
		break;
	case(failure):
		return success;
		break;
	case(running):
		return running;
		break;
	default:
		return failure;
		break;
	}
}

void NotBehaviour::setBehaviour(BehaviourPtr behaviour)
{
	m_behaviour = behaviour;
}

BehaviourPtr NotBehaviour::getBehaviour()
{
	return m_behaviour;
}
