#pragma once
#include "Behaviour.h"
#include "SeekForce.h"
#include "AlignmentForce.h"
#include "CohesionForce.h"
#include "SeparationForce.h"

// Flocks with friendly neighbours
class Flocking : public Behaviour {
public:

	Flocking();
	virtual ~Flocking();

	virtual Behaviour* clone();

	virtual BehaviourResult update(Agent* agent, float deltaTime);
};