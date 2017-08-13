#pragma once
#include "Behaviour.h"
#include "SteeringForce.h"

class SteeringBehaviour :
	public Behaviour
{
public:
	SteeringBehaviour();
	SteeringBehaviour(SteeringForcePtr force);

	//TODO copy constructor (deep copy force)

	virtual ~SteeringBehaviour();

	virtual Behaviour* clone();

	virtual BehaviourResult update(Agent* agent, float deltaTime);

	virtual void draw(Agent* agent, aie::Renderer2D* renderer);

	SteeringForcePtr m_force;
};