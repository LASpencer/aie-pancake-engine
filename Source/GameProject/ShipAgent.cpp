#include "stdafx.h"
#include "ShipAgent.h"
#include "Entity.h"
#include "KeyboardController.h"
#include "DrunkenModifier.h"

ShipAgent::ShipAgent() : Agent()
{
	m_behaviours.push_back(std::make_shared<KeyboardController>());
	m_behaviours.push_back(std::make_shared<DrunkenModifier>());
}

ShipAgent::ShipAgent(float maxVelocity, float maxForce) : Agent(maxVelocity,maxForce)
{
}

ShipAgent::~ShipAgent()
{
}

void ShipAgent::update(float deltaTime)
{
	EntityPtr entity(m_entity);
	//TODO sensing and thinking?
	for (auto it = m_behaviours.begin(); it != m_behaviours.end(); ++it) {
		(*it)->update(entity, deltaTime);
	}
	Agent::update(deltaTime);
}
