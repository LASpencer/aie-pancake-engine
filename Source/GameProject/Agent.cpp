#include "stdafx.h"
#include "Agent.h"
#include "Entity.h"
#include "utility.h"
#include "GameProjectApp.h"
#include "BoundsForce.h"
#include "AvoidTerrainForce.h"


const float Agent::def_max_velocity = 500.f;
const float Agent::def_max_force = 100.f;

Agent::Agent() : Component(), m_maxVelocity(def_max_velocity), m_maxForce(def_max_force), m_velocity(0), m_force(0)
{
	m_stayInBounds = std::make_shared<BoundsForce>();
	m_avoidImpassableTerrain = std::make_shared<AvoidTerrainForce>();
}

Agent::Agent(float maxVelocity, float maxForce) : Component(), m_maxVelocity(maxVelocity), m_maxForce(maxForce), m_velocity(0), m_force(0)
{
	m_stayInBounds = std::make_shared<BoundsForce>();
	m_avoidImpassableTerrain = std::make_shared<AvoidTerrainForce>();
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

void Agent::addForce(SteeringForcePtr force, float weight)
{
	m_steeringForces.push_back({ force, weight });
}

void Agent::update(float deltaTime)
{
	EntityPtr entity(m_entity);
	// Get current square and adjust maximum speed for terrain
	m_square = entity->getApp()->getGrid()->getSquare(getPosition());
	m_adjustedMaxVelocity = m_maxVelocity * m_square->getSpeedFactor();
	// Clear forces
	m_steeringForces.clear();
	// Add default forces
	m_steeringForces.push_back({ std::dynamic_pointer_cast<SteeringForce>(m_stayInBounds), 1.f });
	m_steeringForces.push_back({ std::dynamic_pointer_cast<SteeringForce>(m_avoidImpassableTerrain), 1.f });
	// Get additional forces and actions from behaviour
	m_behaviour->update(this, deltaTime);

	// Weighted truncated combination of forces
	glm::vec2 totalForce(0);
	for (WeightedForce steeringForce : m_steeringForces) {
		totalForce += steeringForce.force->getForce(this) * steeringForce.weight;
		if (glm::dot(totalForce, totalForce) > m_maxForce * m_maxForce) {
			utility::clamp(totalForce, m_maxForce);
			break;
		}
	}
	m_force = totalForce;

	// Update timers
	for (auto timer : m_timers) {
		timer.second.update(deltaTime);
	}
}

void Agent::moveAgent(float deltaTime)
{
	EntityPtr entity(m_entity);
	glm::vec2 displacement(0);
	m_velocity = utility::clamp(m_velocity + (deltaTime  * m_force), m_adjustedMaxVelocity);

	m_force = glm::vec2(0);

	displacement += deltaTime * m_velocity;

	entity->getPosition()->globalTranslate(displacement);

	if (m_velocity != glm::vec2(0)) {
		glm::vec2 heading = glm::normalize(m_velocity);
		glm::vec2 currentAngle = glm::normalize(glm::vec2(glm::vec3(0, 1, 0) * entity->getPosition()->getGlobalTransform()));
		float rotationNeeded = atan2f(currentAngle.y, currentAngle.x) - atan2f(heading.y, -heading.x);
		entity->getPosition()->rotate(rotationNeeded);
	}
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


GameTimer & Agent::getTimer(TimerID id)
{
	return m_timers[id];
}

glm::vec2 Agent::getPosition()
{
	EntityPtr entity(m_entity);

	return glm::vec2(entity->getPosition()->getGlobalTransform()[2]);
}

GridSquarePtr Agent::getSquare()
{
	return m_square;
}

void Agent::setBehaviour(BehaviourPtr behaviour)
{
	m_behaviour = behaviour;
}

