#pragma once
#include "SteeringForce.h"
#include "Agent.h"

class StopForce;
typedef std::shared_ptr<StopForce> StopForcePtr;

class StopForce : public SteeringForce {
public:
	StopForce();

	virtual ~StopForce();

	virtual glm::vec2 getForce(Agent* agent);
};