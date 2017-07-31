#include "stdafx.h"
#include "ChaseyStates.h"

const float ChaseState::chase_max_velocity = 100.f;
const float ChaseState::chase_max_force = 500.f;

const float FleeState::flee_max_velocity = 80.f;
const float FleeState::flee_max_force = 500.f;

ChaseState::ChaseState()
{
}

ChaseState::ChaseState(const ChaseState & other) : State<Agent*>(other), m_chaseTarget(other.m_chaseTarget)
{
}

ChaseState::~ChaseState()
{
}

State<Agent*> * ChaseState::clone() const
{
	return new ChaseState(*this);
}

void ChaseState::setTarget(EntityTargetPtr target)
{
	m_chaseTarget.setTarget(target);
}

void ChaseState::onEnter(Agent * agent)
{
	agent->setMaxForce(chase_max_force);
	agent->setMaxVelocity(chase_max_velocity);
}

void ChaseState::onExit(Agent * agent)
{
}

void ChaseState::update(Agent * entity, StateMachine<Agent*>* sm, float deltaTime)
{
	entity->addForce(m_chaseTarget.getForce(entity));
	State::update(entity, sm, deltaTime);
}

FleeState::FleeState()
{
}

FleeState::FleeState(const FleeState & other) : State<Agent*>(other), m_evadeTarget(other.m_evadeTarget)
{
}

FleeState::~FleeState()
{
}

State<Agent*> * FleeState::clone() const
{
	return new FleeState(*this);
}

void FleeState::setTarget(EntityTargetPtr target)
{
}

void FleeState::onEnter(Agent * agent)
{
	agent->setMaxForce(flee_max_force);
	agent->setMaxVelocity(flee_max_velocity);
	agent->resetTime();
}

void FleeState::onExit(Agent * agent)
{
}

void FleeState::update(Agent * entity, StateMachine<Agent*>* sm, float deltaTime)
{
	entity->addForce(m_evadeTarget.getForce(entity));
	State::update(entity, sm, deltaTime);
}
