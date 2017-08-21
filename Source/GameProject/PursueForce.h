#pragma once
#include "stdafx.h"
#include "SteeringForce.h"
#include "Target.h"

class PursueForce;
typedef std::shared_ptr<PursueForce> PursueForcePtr;

class PursueForce :
	public SteeringForce
{
public:
	static const float def_target_size;

	PursueForce();

	PursueForce(const PursueForce& other);

	PursueForce& operator=(const PursueForce& other);

	virtual ~PursueForce();

	//TODO set target size

	virtual glm::vec2 getForce(Agent* agent);
};