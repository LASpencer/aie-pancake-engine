#pragma once
#include "Behaviour.h"
#include "PursueForce.h"
#include "Target.h"
// TODO rewrite as method of agent

//class MoveToTarget : public Behaviour {
//public:
//	MoveToTarget();
//	MoveToTarget(TargetPtr target);
//	virtual ~MoveToTarget();
//
//	virtual Behaviour* clone();
//
//	virtual BehaviourResult update(Agent* agent, float deltaTime);
//
//	void setTarget(TargetPtr target);
//
//protected:
//	std::shared_ptr<PursueForce> m_force;
//
//};