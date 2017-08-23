#pragma once
#include "Behaviour.h"
#include "SeekForce.h"
#include "AlignmentForce.h"
#include "CohesionForce.h"
#include "SeparationForce.h"

//TODO add separation and alignment forces
//on update, gets neighbours and passesto separation and alignment forces

class Flocking : public Behaviour {
public:

	Flocking();
	virtual ~Flocking();

	virtual Behaviour* clone();

	virtual BehaviourResult update(Agent* agent, float deltaTime);
};