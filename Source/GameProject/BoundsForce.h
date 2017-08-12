#pragma once
#include "SteeringForce.h"

typedef std::shared_ptr<BoundsForce> BoundsForcePtr;

class BoundsForce :
	public SteeringForce
{
public:
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