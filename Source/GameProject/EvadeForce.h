#pragma once
#include "stdafx.h"
#include "SteeringForce.h"
#include "Target.h"

class EvadeForce : public SteeringForce
{
public:
	static const float def_target_size;

	EvadeForce();
	EvadeForce(TargetPtr target);

	EvadeForce(const EvadeForce& other);

	EvadeForce& operator=(const EvadeForce& other);

	virtual ~EvadeForce();

	void setTarget(TargetPtr target);

	virtual glm::vec2 getForce(Agent* agent);

protected:
	TargetPtr m_target;
};