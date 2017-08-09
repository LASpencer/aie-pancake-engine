#pragma once
#include "Behaviour.h"
#include "SeekForce.h"

//TODO add separation and alignment forces
//on update, gets neighbours and passesto separation and alignment forces

class Flocking : public Behaviour {
public:
	Flocking();
	virtual ~Flocking();

	virtual Behaviour* clone();

	virtual BehaviourResult update(Agent* entity, float deltaTime);

protected:
	float m_separationWeight, m_alignmentWeight, m_cohesionWeight;
	float m_range;
	bool(*isBoidRule)(Agent*);
};