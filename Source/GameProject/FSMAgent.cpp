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

bool FSMAgent::onAdd(EntityPtr entity)
{
	bool added = isValidEntity(entity) && Agent::onAdd(entity);

	return added;
}

void FSMAgent::update(float deltaTime)
{
}

bool FSMAgent::isValidEntity(EntityPtr entity)
{
	//Might add extra requirements?
	Agent::isValidEntity(entity);
}

StateMachine<FSMAgent>& FSMAgent::getStateMachine()
{
	return m_stateMachine;
}
