#pragma once
#include "Behaviour.h"

class DeathBehaviour : public Behaviour {
public:
	DeathBehaviour();

	virtual ~DeathBehaviour();

	virtual Behaviour* clone();

	virtual BehaviourResult update(Agent* agent, float deltaTime);

};