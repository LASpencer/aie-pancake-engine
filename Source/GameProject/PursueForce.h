#pragma once
#include "stdafx.h"
#include "SteeringForce.h"
#include "Target.h"

class PursueForce :
	public SteeringForce
{
public:
	static const float def_target_size;

	PursueForce();

	PursueForce(Target* target);

	PursueForce(const PursueForce& other);

	PursueForce& operator=(const PursueForce& other);

	virtual ~PursueForce();

	void setTarget(Target* target);

	//TODO set target size

	virtual glm::vec2 getForce(Agent* agent);

protected:
	Target* m_target;
};