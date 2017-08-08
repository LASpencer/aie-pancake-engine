#include "stdafx.h"
#include "SimpleAgent.h"
#include "Entity.h"
#include "KeyboardController.h"
#include "DrunkenModifier.h"

SimpleAgent::SimpleAgent() : Agent()
{
}

SimpleAgent::SimpleAgent(float maxVelocity, float maxForce) : Agent(maxVelocity,maxForce)
{
}

SimpleAgent::~SimpleAgent()
{
}

void SimpleAgent::update(float deltaTime)
{
	EntityPtr entity(m_entity);
	for (auto it = m_behaviours.begin(); it != m_behaviours.end(); ++it) {
		(*it)->update(this, deltaTime);
	}
	Agent::update(deltaTime);
}

void SimpleAgent::draw(aie::Renderer2D * renderer)
{
	for (auto it = m_behaviours.begin(); it != m_behaviours.end(); ++it) {
		(*it)->draw(this, renderer);
	}
}
