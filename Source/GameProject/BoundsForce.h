#pragma once
#include "SteeringForce.h"

class BoundsForce :
	public SteeringForce
{
	static const float def_max_x;
	static const float def_max_y;

	BoundsForce();

	BoundsForce(float minX, float maxX, float minY, float maxY);

	virtual ~BoundsForce();

	void setBounds(float minX, float maxX, float minY, float maxY);

	virtual glm::vec2 getForce(Agent* agent);

protected:
	float m_minX, m_minY, m_maxX, m_maxY;
};