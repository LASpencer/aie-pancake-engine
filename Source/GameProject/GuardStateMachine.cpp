#include "stdafx.h"
#include "GuardStateMachine.h"
#include "GuardStates.h"

const float GuardStateMachine::def_near_range = 100.f;
const float GuardStateMachine::def_far_range = 200.f;
const float GuardStateMachine::def_wait_time = 5.f;

GuardStateMachine::GuardStateMachine()
{
	m_targetClose = std::make_shared<TargetInRangeCondition>();
	m_targetNotFar = std::make_shared<TargetInRangeCondition>();
	m_waitTime = std::make_shared<TimerCondition>();
	m_targetClose->setRange(def_near_range);
	m_targetNotFar->setRange(def_far_range);
	m_waitTime->setTime(def_wait_time);

	std::shared_ptr<NotCondition<Agent*>> targetFar = std::make_shared<NotCondition<Agent*>>(m_targetNotFar);
	//TODO add transitions to states

	std::shared_ptr<Transition<Agent*>> startAttack = std::make_shared<Transition<Agent*>>(m_targetClose, attack);
	std::shared_ptr<IdleState> idleState = std::make_shared<IdleState>();
	idleState->addTransition(startAttack);
	idleState->addTransition(std::make_shared<Transition<Agent*>>(m_waitTime, patrol));
	addState(idle, idleState);

	std::shared_ptr<PatrolState> patrolState = std::make_shared<PatrolState>();
	patrolState->addTransition(startAttack);
	addState(patrol, patrolState);
	
	std::shared_ptr<AttackState> attackState = std::make_shared<AttackState>();
	attackState->addTransition(std::make_shared<Transition<Agent*>>(targetFar, idle));
	addState(attack, attackState);
}

GuardStateMachine::GuardStateMachine(std::vector<glm::vec2> route, EntityPtr target) : m_target(target)
{
	m_targetClose = std::make_shared<TargetInRangeCondition>(&m_target, def_near_range);
	m_targetNotFar = std::make_shared<TargetInRangeCondition>(&m_target, def_far_range);
	m_waitTime = std::make_shared<TimerCondition>(def_wait_time);

	std::shared_ptr<NotCondition<Agent*>> targetFar = std::make_shared<NotCondition<Agent*>>(m_targetNotFar);
	//add transitions to states

	std::shared_ptr<Transition<Agent*>> startAttack = std::make_shared<Transition<Agent*>>(m_targetClose, attack);
	std::shared_ptr<IdleState> idleState = std::make_shared<IdleState>();
	idleState->addTransition(startAttack);
	idleState->addTransition(std::make_shared<Transition<Agent*>>(m_waitTime, patrol));
	addState(idle, idleState);

	std::shared_ptr<PatrolState> patrolState = std::make_shared<PatrolState>(route);
	patrolState->addTransition(startAttack);
	addState(patrol, patrolState);

	std::shared_ptr<AttackState> attackState = std::make_shared<AttackState>(&m_target);
	attackState->addTransition(std::make_shared<Transition<Agent*>>(targetFar, idle));
	addState(attack, attackState);
}

GuardStateMachine::~GuardStateMachine()
{
}

void GuardStateMachine::setTarget(EntityPtr target)
{
	m_target.setTarget(target);
	std::dynamic_pointer_cast<AttackState>(m_states[attack])->setTarget(&m_target);
	m_targetClose->setTarget(&m_target);
	m_targetNotFar->setTarget(&m_target);
}

void GuardStateMachine::setRoute(std::vector<glm::vec2> route)
{
	std::dynamic_pointer_cast<PatrolState>(m_states[patrol])->setRoute(route);
}

void GuardStateMachine::setNearRange(float near)
{
	m_targetClose->setRange(near);
}

void GuardStateMachine::setFarRange(float far)
{
	m_targetNotFar->setRange(far);
}

void GuardStateMachine::setWaitTime(float time)
{
	m_waitTime->setTime(time);
}
