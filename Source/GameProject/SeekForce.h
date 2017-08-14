#pragma once
#include "stdafx.h"
#include "SteeringForce.h"
#include "Target.h"

class SeekForce;
typedef std::shared_ptr<SeekForce> SeekForcePtr;

class SeekForce :
	public SteeringForce
{
public:
	SeekForce();

	SeekForce(TargetPtr target); 

	SeekForce(const SeekForce& other);

	SeekForce& operator=(const SeekForce& other);

	virtual ~SeekForce();

	void setTarget(TargetPtr target);

	virtual glm::vec2 getForce(Agent* agent);

protected:
	TargetPtr m_target; //TODO change to shared_ptr
};