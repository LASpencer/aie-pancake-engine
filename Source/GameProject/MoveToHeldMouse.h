#pragma once
#include "Behaviour.h"

class MoveToHeldMouse : public Behaviour {
public:
	MoveToHeldMouse();

	virtual ~MoveToHeldMouse();
	
	virtual Behaviour* clone();

	virtual BehaviourResult update(Agent* agent, float deltaTime);
};