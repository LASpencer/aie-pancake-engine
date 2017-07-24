#include "stdafx.h"
#include "FSMBehaviour.h"

FSMBehaviour::FSMBehaviour() : m_stateMachine()
{
}

FSMBehaviour::~FSMBehaviour()
{
}

void FSMBehaviour::update(Agent* agent, float deltaTime)
{
	m_stateMachine.update(agent, deltaTime);
}

StateMachine<Agent*>& FSMBehaviour::getStateMachine()
{
	return m_stateMachine;
}
