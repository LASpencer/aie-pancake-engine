#pragma once
#include "stdafx.h"
#include "SteeringForce.h"
#include "Target.h"

class SeekForce :
	public SteeringForce
{
public:
	SeekForce();

	SeekForce(Target* target);

	SeekForce(const SeekForce& other);

	SeekForce& operator=(const SeekForce& other);

	virtual ~SeekForce();

	void setTarget(Target* target);

	virtual glm::vec2 getForce(Agent* agent);

protected:
	Target* m_target;
};