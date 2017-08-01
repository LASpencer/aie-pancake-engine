#pragma once
#include "Behaviour.h"
#include "SteeringForce.h"

class SteeringBehaviour :
	public Behaviour
{
public:
	SteeringBehaviour();
	SteeringBehaviour(SteeringForcePtr force);

	virtual ~SteeringBehaviour();

	virtual BehaviourResult update(Agent* entity, float deltaTime);
	SteeringForcePtr m_force;
};