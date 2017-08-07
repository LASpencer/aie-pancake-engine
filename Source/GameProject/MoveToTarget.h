#pragma once
#include "Behaviour.h"
#include "PursueForce.h"
#include "Target.h"

class MoveToTarget : public Behaviour {
public:
	MoveToTarget();
	MoveToTarget(TargetPtr target);
	virtual ~MoveToTarget();

	virtual Behaviour* clone();

	virtual BehaviourResult update(Agent* entity, float deltaTime);

	void setTarget(TargetPtr target);

protected:
	PursueForce m_force;

};