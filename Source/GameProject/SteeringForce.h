#pragma once
#include "stdafx.h"
#include "Renderer2D.h"

class Agent;
typedef std::shared_ptr<Agent> AgentPtr;
typedef std::weak_ptr<Agent> AgentWeakPtr;

class SteeringForce;

typedef std::shared_ptr<SteeringForce> SteeringForcePtr;

class SteeringForce {
public:
	SteeringForce() {};
	virtual ~SteeringForce() {};

	virtual glm::vec2 getForce(Agent* agent) = 0;

	virtual void draw(Agent* agent, aie::Renderer2D* renderer) {};

protected:
	glm::vec2 seekPoint(Agent* agent, glm::vec2 target);

	glm::vec2 avoidPoint(Agent* agent, glm::vec2 target);

	glm::vec2 arrivePoint(Agent* agent, glm::vec2 target, float radius);
};