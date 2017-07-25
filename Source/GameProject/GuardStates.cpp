#include "stdafx.h"
#include "GuardStates.h"
#include "Agent.h"


IdleState::IdleState() : State<Agent*>()
{
}

IdleState::IdleState(const IdleState & other) : State(other)
{
}

IdleState::~IdleState()
{
}

State<Agent*> * IdleState::clone() const
{
	return new IdleState(*this);
}

void IdleState::onEnter(Agent * agent)
{
	agent->resetTime();
}

void IdleState::onExit(Agent * agent)
{
}

// Patrol State

const float PatrolState::waypoint_size = 2.0f;

PatrolState::PatrolState() : State<Agent*>()
{
	m_route.push_back(PointTarget());
	startRoute();

	m_hasReachedWaypoint.setRange(waypoint_size);
}

PatrolState::PatrolState(std::vector<glm::vec2> route)
{
	setRoute(route);
	startRoute();

	m_hasReachedWaypoint.setRange(waypoint_size);
}

PatrolState::PatrolState(const PatrolState & other) : State(other), m_route(other.m_route)
{
	startRoute();			//Kinda lazy, but this is just an exercise
	m_hasReachedWaypoint.setRange(waypoint_size);
}

PatrolState::~PatrolState()
{
}

State<Agent*> * PatrolState::clone() const
{
	return new PatrolState(*this);
}

void PatrolState::setRoute(std::vector<glm::vec2> route)
{
	m_route.clear();
	for (glm::vec2 waypoint : route) {
		m_route.push_back(PointTarget(waypoint));
	}
}

void PatrolState::onEnter(Agent * agent)
{
}

void PatrolState::onExit(Agent * agent)
{
}

void PatrolState::update(Agent * entity, StateMachine<Agent*>* sm, float deltaTime)
{
	//TODO apply steering force towards current waypoint
	entity->addForce(m_seekWaypoint.getForce(entity));
	if (m_hasReachedWaypoint.test(entity)) {
		incrementWaypoint();
	}
	State::update(entity, sm, deltaTime);
}

void PatrolState::incrementWaypoint()
{
	if (m_currentWaypoint == m_route.end()) {
		m_currentWaypoint = m_route.begin();
	} else {
		++m_currentWaypoint;
	}

	m_hasReachedWaypoint.setTarget(&(*m_currentWaypoint));
}

void PatrolState::startRoute()
{
	m_currentWaypoint = m_route.begin();
	m_hasReachedWaypoint.setTarget(&(*m_currentWaypoint));
	m_seekWaypoint.setTarget(&(*m_currentWaypoint));
}
