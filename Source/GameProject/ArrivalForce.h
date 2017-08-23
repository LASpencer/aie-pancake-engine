#pragma once
#include "stdafx.h"
#include "SteeringForce.h"

class ArrivalForce;
typedef std::shared_ptr<ArrivalForce> ArrivalForcePtr;

class ArrivalForce :
	public SteeringForce
{
public:
	static const float def_radius;

	ArrivalForce();

	ArrivalForce(glm::vec2 goal, float radius = def_radius);

	ArrivalForce(const ArrivalForce& other);

	ArrivalForce& operator=(const ArrivalForce& other);

	virtual ~ArrivalForce();

	void setGoal(glm::vec2 goal);

	virtual glm::vec2 getForce(Agent* agent);

protected:
	glm::vec2 m_goal;
	float m_radius;
};