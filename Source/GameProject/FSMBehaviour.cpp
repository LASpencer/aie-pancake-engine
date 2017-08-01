#include "stdafx.h"
#include "FSMBehaviour.h"

FSMBehaviour::FSMBehaviour() : m_stateMachine()
{
}

FSMBehaviour::FSMBehaviour(StateMachine<Agent*>* stateMachine) : m_stateMachine(stateMachine)
{
}

FSMBehaviour::~FSMBehaviour()
{
	delete m_stateMachine;
}

bool FSMBehaviour::update(Agent* agent, float deltaTime)
{
	m_stateMachine->update(agent, deltaTime);
	return true;
}

void FSMBehaviour::setStateMachine(StateMachine<Agent*>* stateMachine)
{
	if (m_stateMachine != nullptr) {
		delete m_stateMachine;
	}
	m_stateMachine = stateMachine;
}

StateMachine<Agent*>* FSMBehaviour::getStateMachine()
{
	return m_stateMachine;
}
