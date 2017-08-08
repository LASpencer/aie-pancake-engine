#include "stdafx.h"
#include "Agent.h"
#include "Entity.h"
#include "utility.h"

//TODO write agent subclass which can give weights to its behaviours

const float Agent::def_max_velocity = 500.f;
const float Agent::def_max_force = 100.f;

Agent::Agent() : Component(), m_maxVelocity(def_max_velocity), m_maxForce(def_max_force), m_velocity(0), m_force(0), m_time(0)
{
}

Agent::Agent(float maxVelocity, float maxForce) : Component(), m_maxVelocity(maxVelocity), m_maxForce(maxForce), m_velocity(0), m_force(0), m_time(0)
{
}

Agent::~Agent()
{
}

void Agent::setVelocity(glm::vec2 velocity)
{
	m_velocity = utility::clamp(velocity, m_maxVelocity);
}

void Agent::applyImpulse(glm::vec2 impulse)
{
	m_velocity = utility::clamp(m_velocity + impulse, m_maxVelocity);
}

void Agent::addForce(glm::vec2 force)
{
	m_force = utility::clamp(m_force + force, m_maxForce);
}

void Agent::update(float deltaTime)
{
	EntityPtr entity(m_entity);

	glm::vec2 displacement(0);

	displacement += 0.5f * deltaTime * m_velocity;

	m_velocity = utility::clamp(m_velocity + (deltaTime  * m_force), m_maxVelocity);

	m_force = glm::vec2(0);

	displacement += 0.5f * deltaTime * m_velocity;

	entity->getPosition()->globalTranslate(displacement);

	if (m_velocity != glm::vec2(0)) {
		glm::vec2 heading = glm::normalize(m_velocity);
		glm::vec2 currentAngle = glm::normalize(glm::vec2(glm::vec3(0, 1, 0) * entity->getPosition()->getGlobalTransform()));
		float rotationNeeded =  atan2f(currentAngle.y, currentAngle.x) - atan2f(heading.y, -heading.x);
		entity->getPosition()->rotate(rotationNeeded);
	}

	m_time += deltaTime;
}


Agent::Identifier Agent::getID()
{
	return agent;
}

void Agent::setMaxVelocity(float maxVelocity)
{
	m_maxVelocity = maxVelocity;
}

void Agent::setMaxForce(float maxForce)
{
	m_maxForce = maxForce;
}

void Agent::resetTime()
{
	m_time = 0.f;
}

glm::vec2 Agent::getPosition()
{
	EntityPtr entity(m_entity);

	return glm::vec2(entity->getPosition()->getGlobalTransform()[2]);
}

void Agent::addBehaviour(BehaviourPtr behaviour)
{
	m_behaviours.push_back(behaviour);
}

void Agent::setBehaviours(std::vector<BehaviourPtr> behaviours)
{
	m_behaviours = behaviours;
}

