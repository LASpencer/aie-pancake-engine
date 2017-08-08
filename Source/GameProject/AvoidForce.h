#pragma once
#include "SteeringForce.h"
#include "Ray.h"

class AvoidForce : public SteeringForce {
public:
	AvoidForce();

	virtual ~AvoidForce();

	virtual glm::vec2 getForce(Agent* agent);

	virtual void draw(Agent* agent, aie::Renderer2D* renderer);

protected:
	std::vector<Ray> m_rays;
};