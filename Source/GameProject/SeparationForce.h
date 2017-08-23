#pragma once
#include "SteeringForce.h"

// Stay away from neighbours, either friendly or enemy
class SeparationForce : public SteeringForce {
public:
	SeparationForce(bool fleeEnemies = false);
	virtual ~SeparationForce();

	virtual glm::vec2 getForce(Agent* agent);

	void setFleeEnemies(bool fleeEnemies);

protected:
	bool m_fleeEnemies;
};