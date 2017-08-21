#pragma once
#include "Behaviour.h"
#include "VehicleAgent.h"

class AtBaseQuestion : public Behaviour {
public:
	static const float base_size;

	AtBaseQuestion();
	virtual ~AtBaseQuestion();

	virtual Behaviour* clone();

	virtual BehaviourResult update(Agent* agent, float deltaTime);
};