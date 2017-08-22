#pragma once
#include "Behaviour.h"

class ChaseTarget : public Behaviour {
public:
	ChaseTarget();

	virtual ~ChaseTarget();

	virtual Behaviour* clone();

	virtual BehaviourResult update(Agent* agent, float deltaTime);
};