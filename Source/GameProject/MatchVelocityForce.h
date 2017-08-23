#pragma once
#include "SteeringForce.h"

// Try to match velocity with target
class MatchVelocityForce : public SteeringForce {
public:
	MatchVelocityForce();
	virtual ~MatchVelocityForce();

	virtual glm::vec2 getForce(Agent* agent);
};