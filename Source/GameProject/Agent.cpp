#include "stdafx.h"
#include "Agent.h"
#include "Entity.h"
#include "utility.h"
#include "GameProjectApp.h"
#include "BoundsForce.h"
#include "AvoidTerrainForce.h"
#include "SeekForce.h"
#include "Target.h"
#include "CollisionEvent.h"
#include "PursueForce.h"
#include "ArrivalForce.h"
#include "StopForce.h"

const float Agent::def_max_velocity = 500.f;
const float Agent::def_max_force = 100.f;
const float Agent::def_size = 50.f;

Agent::Agent() : Component(), m_maxVelocity(def_max_velocity), m_maxForce(def_max_force), m_velocity(0), m_force(0), m_canMove(true)
{
	m_stayInBounds = std::make_shared<BoundsForce>();
	m_avoidImpassableTerrain = std::make_shared<AvoidTerrainForce>();
	m_pursueTarget = std::make_shared<PursueForce>();
	m_stopForce = std::make_shared<StopForce>();
}

Agent::Agent(float maxVelocity, float maxForce, float size) : Component(), m_maxVelocity(maxVelocity), m_maxForce(maxForce), m_size(size), m_velocity(0), m_force(0), m_canMove(true)
{
	m_stayInBounds = std::make_shared<BoundsForce>();
	m_avoidImpassableTerrain = std::make_shared<AvoidTerrainForce>();
	m_pursueTarget = std::make_shared<PursueForce>();
	m_stopForce = std::make_shared<StopForce>();
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
	if (m_canMove) {
		m_adjustedMaxVelocity = m_maxVelocity * m_square->getSpeedFactor();
	} else {
		m_adjustedMaxVelocity = 0.f;
	}
	// Clear forces
	m_steeringForces.clear();
	// Add default forces
	addDefaultForces();
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
		m_timers[timer.first].update(deltaTime);
	}
}

void Agent::draw(aie::Renderer2D * renderer)
{
	// Draw current path
	if (!m_path.empty()) {
		glm::vec2 oldPosition = getPosition();
		glm::vec2 nextPosition;
		std::stack<GridSquarePtr> pathCopy = m_path;
		renderer->setRenderColour(0x8000ffff);
		while (!pathCopy.empty()) {
			nextPosition = pathCopy.top()->getPosition();
			pathCopy.pop();
			renderer->drawLine(oldPosition.x, oldPosition.y, nextPosition.x, nextPosition.y, 3.f);
			oldPosition = nextPosition;
		}
		nextPosition = m_goal;
		renderer->drawLine(oldPosition.x, oldPosition.y, nextPosition.x, nextPosition.y, 3.f);
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

void Agent::setSize(float size)
{
	m_size = size;
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

void Agent::setTarget(AgentPtr target)
{
	m_target = target;
}

AgentPtr Agent::getTarget()
{
	return m_target;
}

void Agent::setBehaviour(BehaviourPtr behaviour)
{
	m_behaviour = behaviour;
}

bool Agent::setGoal(glm::vec2 goal)
{
	bool success = false;
	EntityPtr entity(m_entity);
	Grid* grid = entity->getApp()->getGrid();
	GridSquarePtr endSquare = grid->getSquare(goal);
	if (endSquare == m_goalSquare && !m_path.empty() && m_path.top()->isInSelfOrNeighbour(getPosition())) {
		m_goal = goal;
		success = true;
	}
	else {
		std::stack<GridSquarePtr> path = grid->findPath(m_square, endSquare);
		// Check if path was found
		if (!path.empty()) {
			m_goal = goal;
			m_path = path;
			m_goalSquare = endSquare;
			success = true;
		}
	}
	return success;
}

void Agent::addDefaultForces()
{
	m_steeringForces.push_back({ std::dynamic_pointer_cast<SteeringForce>(m_stayInBounds), 1.f });
	m_steeringForces.push_back({ std::dynamic_pointer_cast<SteeringForce>(m_avoidImpassableTerrain), 1.f });
}

void Agent::followPath(float weight)
{
	EntityPtr entity(m_entity);
	Grid* grid = entity->getApp()->getGrid();
	GridSquarePtr endSquare = grid->getSquare(m_goal);
	SteeringForcePtr force;

	if (m_square == endSquare) {
		ArrivalForcePtr arrive(std::make_shared<ArrivalForce>(m_goal)); //TODO rewrite as "ArrivePointForce" or sth
		force = std::dynamic_pointer_cast<SteeringForce>(arrive);
		m_steeringForces.push_back({ force, weight });
	} else if (!m_path.empty()) {
		SeekForcePtr seek(std::make_shared<SeekForce>(m_path.top()->getPosition())); //TODO rewrite as "SeekPointForce" or sth
		force = std::dynamic_pointer_cast<SteeringForce>(seek);
		m_steeringForces.push_back({ force, weight });
		if (m_path.top() == m_square) {
			m_path.pop();
		}
	}
}

void Agent::matchTargetVelocity(float weight)
{
	//TODO write matchVelocity steering force
}

void Agent::stop(float weight)
{
	m_steeringForces.push_back({ std::dynamic_pointer_cast<SteeringForce>(m_stopForce), weight });
}

bool Agent::pursueTarget(float weight)
{
	if (canMove()) {
		m_steeringForces.push_back({ std::dynamic_pointer_cast<SteeringForce>(m_pursueTarget), weight });
		return true;
	}
	return false;
}

void Agent::notify(Subject * subject, EventBase * event)
{
	//TODO if terrain collision, or body collided with other body, apply impulse for collision
	EventBase::EventID id = event->getEventID();
	if (id == EventBase::collision) {
		CollisionEvent* collisionEvent = dynamic_cast<CollisionEvent*>(event);
		//TODO check subject is collider, if body-body impulse away
		if (collisionEvent->getMyType() == body && collisionEvent->getOtherType() == body) {
			applyImpulse(collisionEvent->getPenetration() * 0.5f);
		}
	}
	else if (id == EventBase::terrain_collision) {
		TerrainCollisionEvent* collisionEvent = dynamic_cast<TerrainCollisionEvent*>(event);
		//TODO check subject is collider, square isn't expired
		if (collisionEvent->getMyType() == body &&
			collisionEvent->getSquare().lock()->getType() == impassable) {
			applyImpulse(collisionEvent->getPenetration());
		}
	}
}

bool Agent::addSubject(Subject * subject)
{
	return true;
}

void Agent::removeSubject(Subject * subject)
{
}

bool Agent::canMove()
{
	return  m_canMove;
}

