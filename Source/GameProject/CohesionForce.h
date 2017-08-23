#pragma once
#include "SteeringForce.h"

// Move towards average position of neighbours
class CohesionForce : public SteeringForce {
public:
	CohesionForce();
	virtual ~CohesionForce();

	virtual glm::vec2 getForce(Agent* agent);

};