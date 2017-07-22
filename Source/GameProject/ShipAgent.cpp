#include "stdafx.h"
#include "ShipAgent.h"
#include "Entity.h"
#include "KeyboardController.h"

ShipAgent::ShipAgent() : Agent()
{
	m_behaviours.push_back(std::make_shared<KeyboardController>());
}

ShipAgent::ShipAgent(float maxVelocity, float maxForce) : Agent(maxVelocity,maxForce)
{
}

ShipAgent::~ShipAgent()
{
}

bool ShipAgent::onAdd(EntityPtr entity)
{
	bool added = isValidEntity(entity) && Agent::onAdd(entity);

	return added;
}

void ShipAgent::update(float deltaTime)
{
	EntityPtr entity(m_entity);
	//TODO sensing and thinking?
	for (auto it = m_behaviours.begin(); it != m_behaviours.end(); ++it) {
		(*it)->update(entity, deltaTime);
	}
}

bool ShipAgent::isValidEntity(EntityPtr entity)
{
	//can have extra requirements
	Agent::isValidEntity(entity);
}
