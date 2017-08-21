#pragma once
#include "Behaviour.h"
#include "PursueForce.h"
#include "Target.h"

class AttackTarget : public Behaviour {
public:
	AttackTarget();
	virtual ~AttackTarget();

	virtual Behaviour* clone();

	virtual BehaviourResult update(Agent* agent, float deltaTime);
};