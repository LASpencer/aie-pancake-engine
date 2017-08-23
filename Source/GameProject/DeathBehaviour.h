#pragma once
#include "Behaviour.h"

// Dead tank does nothing, and respawns after a few seconds
class DeathBehaviour : public Behaviour {
public:
	DeathBehaviour();

	virtual ~DeathBehaviour();

	virtual Behaviour* clone();

	virtual BehaviourResult update(Agent* agent, float deltaTime);

};