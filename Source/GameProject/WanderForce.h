#pragma once
#include "stdafx.h"
#include "SteeringForce.h"
#include <random>

// Force to move around making random turns
class WanderForce :
	public SteeringForce
{
public:
	static const float def_radius;
	static const float def_jitter;
	static const float def_distance;

	WanderForce();

	WanderForce(float radius, float jitter, float distance);

	void setRadius(float radius);

	void setJitter(float jitter);

	void setDistance(float distance);

	virtual glm::vec2 getForce(Agent* agent);

private:
	float m_radius;
	float m_jitter;
	float m_distance;
	glm::vec2 m_target;
};