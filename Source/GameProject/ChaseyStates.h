#pragma once
#include "State.h"
#include "TargetInRangeCondition.h"
#include "Target.h"
#include "PursueForce.h"
#include "EvadeForce.h"


//TODO chase state, flee state, idle state
// When caught, chaser becomes fleer, fleer becomes idle
// Idle goes to chase after time
//
//class Agent;
//
////chase state
//class ChaseState : public State<Agent*>
//{
//public:
//	static const float chase_max_velocity;
//	static const float chase_max_force;
//
//	ChaseState();
//
//	ChaseState(const ChaseState& other);
//
//	virtual ~ChaseState();
//
//	virtual State* clone() const;
//
//	void setTarget(EntityTargetPtr target);
//
//	virtual void onEnter(Agent* agent);
//	virtual void onExit(Agent* agent);
//	virtual void update(Agent* entity, StateMachine<Agent*>* sm, float deltaTime);
//
//protected:
//	PursueForce m_chaseTarget;
//};
//
////flee state
//class FleeState : public State<Agent*>
//{
//public:
//	static const float flee_max_velocity;
//	static const float flee_max_force;
//
//	FleeState();
//
//	FleeState(const FleeState& other);
//
//	virtual ~FleeState();
//
//	virtual State* clone() const;
//
//	void setTarget(EntityTargetPtr target);
//
//	virtual void onEnter(Agent* agent);
//	virtual void onExit(Agent* agent);
//	virtual void update(Agent* entity, StateMachine<Agent*>* sm, float deltaTime);
//
//protected:
//	EvadeForce m_evadeTarget;
//};