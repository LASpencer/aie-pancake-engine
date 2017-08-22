#pragma once
#include "SteeringForce.h"

class MatchVelocityForce : public SteeringForce {
public:
	MatchVelocityForce();
	virtual ~MatchVelocityForce();

	virtual glm::vec2 getForce(Agent* agent);
};