#pragma once
#include "stdafx.h"
#include "SteeringForce.h"

class PursueForce;
typedef std::shared_ptr<PursueForce> PursueForcePtr;

// Pursue target
class PursueForce :
	public SteeringForce
{
public:
	static const float def_target_size;

	PursueForce();

	PursueForce(const PursueForce& other);

	PursueForce& operator=(const PursueForce& other);

	virtual ~PursueForce();

	virtual glm::vec2 getForce(Agent* agent);
};