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

	PursueForce(TargetPtr target);

	PursueForce(const PursueForce& other);

	PursueForce& operator=(const PursueForce& other);

	virtual ~PursueForce();

	void setTarget(TargetPtr target);

	//TODO set target size

	virtual glm::vec2 getForce(Agent* agent);

protected:
	TargetPtr m_target;
};