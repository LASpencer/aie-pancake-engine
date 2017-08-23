#pragma once
#include "Behaviour.h"

// Pathfinds towards held down mouse button
class MoveToHeldMouse : public Behaviour {
public:
	MoveToHeldMouse();

	virtual ~MoveToHeldMouse();
	
	virtual Behaviour* clone();

	// Succeeds if path found, otherwise fails
	virtual BehaviourResult update(Agent* agent, float deltaTime);
};