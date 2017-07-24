#include "stdafx.h"
#include "FSMAgent.h"
#include "Entity.h"

FSMAgent::FSMAgent() : Agent(), m_stateMachine()
{
}

FSMAgent::FSMAgent(float maxVelocity, float maxForce) : Agent(maxVelocity, maxForce)
{
}


FSMAgent::~FSMAgent()
{
}

void FSMAgent::update(float deltaTime)
{
	Agent::update(deltaTime);
}

StateMachine<FSMAgent>& FSMAgent::getStateMachine()
{
	return m_stateMachine;
}
