#pragma once
#include "stdafx.h"
#include "Agent.h"

class SteeringForce {
public:
	SteeringForce() {};
	virtual ~SteeringForce() {};

	virtual glm::vec2 getForce(Agent* agent) = 0;

protected:
	glm::vec2 seekPoint(Agent* agent, glm::vec2 target);

	glm::vec2 avoidPoint(Agent* agent, glm::vec2 target);

	glm::vec2 arrivePoint(Agent* agent, glm::vec2 target, float radius);
};