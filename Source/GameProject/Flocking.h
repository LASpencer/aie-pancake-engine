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
	static const float def_separation_weight;
	static const float def_alignment_weight;
	static const float def_cohesion_weight;
	static const float def_range;

	Flocking();
	Flocking(bool(*boidRule)(Agent*), float separationWeight = def_separation_weight, float alignmentWeight = def_alignment_weight, float cohesionWeight = def_cohesion_weight, float range = def_range);
	virtual ~Flocking();

	virtual Behaviour* clone();

	virtual BehaviourResult update(Agent* agent, float deltaTime);
	void setRule(bool (*newBoidRule)(Agent*));


	float m_separationWeight, m_alignmentWeight, m_cohesionWeight;
	float m_range;
protected:
	AlignmentForce m_alignment;
	CohesionForce m_cohesion;
	SeparationForce m_separation;
	bool(*isBoidRule)(Agent*);
};