#pragma once
#include "Behaviour.h"
#include "VehicleAgent.h"

// Returns success if friends outnumbered by enemies
class OutnumberedQuestion : public Behaviour {
public:
	OutnumberedQuestion();

	virtual ~OutnumberedQuestion();

	virtual Behaviour* clone();

	virtual BehaviourResult update(Agent* agent, float deltaTime);
};