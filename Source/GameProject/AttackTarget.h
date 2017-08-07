#pragma once
#include "Behaviour.h"
#include "PursueForce.h"
#include "Target.h"

class AttackTarget : public Behaviour {
public:
	AttackTarget();
	AttackTarget(TargetPtr target);
	virtual ~AttackTarget();

	virtual Behaviour* clone();

	virtual BehaviourResult update(Agent* entity, float deltaTime);

	void setTarget(TargetPtr target);

protected:
	PursueForce m_force;

};