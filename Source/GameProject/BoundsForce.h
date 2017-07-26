#pragma once
#include "SteeringForce.h"

class BoundsForce :
	public SteeringForce
{
	BoundsForce();

	BoundsForce(float minX, float maxX, float minY, float maxY);

	void setBounds(float minX, float maxX, float minY, float maxY);

	virtual glm::vec2 getForce(Agent* agent);

protected:
	float m_minX, m_minY, m_maxX, m_maxY;
};