#pragma once
#include "State.h"
#include "TargetInRangeCondition.h"
#include "Target.h"
#include "SeekForce.h"
#include "ArrivalForce.h"
#include "PursueForce.h"

//class Agent;
//
////Idle state
//class IdleState : public State<Agent*>
//{
//public:
//	IdleState();
//
//	IdleState(const IdleState& other);
//
//	virtual ~IdleState();
//
//	virtual State* clone() const;
//
//	virtual void onEnter(Agent* agent);
//	virtual void onExit(Agent* agent);
//	virtual void update(Agent* entity, StateMachine<Agent*>* sm, float deltaTime);
//};
//
////Patrol state
//class PatrolState : public State<Agent*>
//{
//public:
//	static const float waypoint_size;
//
//	PatrolState();
//	PatrolState(std::vector<glm::vec2> route);
//	PatrolState(const PatrolState& other);
//	virtual ~PatrolState();
//
//	virtual State* clone() const;
//
//	void setRoute(std::vector<glm::vec2> route);
//
//	virtual void onEnter(Agent* agent);
//
//	virtual void onExit(Agent* agent);
//
//	virtual void update(Agent* entity, StateMachine<Agent*>* sm, float deltaTime);
//
//protected:
//	std::vector<PointTargetPtr> m_route;
//	std::vector<PointTargetPtr>::iterator m_currentWaypoint;
//	TargetInRangeCondition m_hasReachedWaypoint;
//
//	ArrivalForce m_seekWaypoint;
//
//	void incrementWaypoint();
//
//	void startRoute();
//};
//
//
////Attack state
//class AttackState : public State<Agent*>
//{
//public:
//	AttackState();
//	AttackState(EntityTargetPtr target);
//	AttackState(const AttackState& other);
//	virtual ~AttackState();
//
//	virtual State* clone() const;
//
//	void setTarget(EntityTargetPtr target);
//
//	virtual void onEnter(Agent* agent);
//
//	virtual void onExit(Agent* agent);
//
//	virtual void update(Agent* entity, StateMachine<Agent*>* sm, float deltaTime);
//
//protected:
//	PursueForce m_attackTarget;
//};