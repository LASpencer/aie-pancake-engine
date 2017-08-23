#pragma once
#include "SteeringForce.h"

// Tries to make velocity the average of neighbours' velocities
class AlignmentForce : public SteeringForce {
public:
	AlignmentForce();
	virtual ~AlignmentForce();

	virtual glm::vec2 getForce(Agent* agent);

};