#pragma once
#include "SteeringForce.h"
#include "Target.h"

class ArrivalForce :
	public SteeringForce
{
public:
	static const float def_radius;

	ArrivalForce();

	ArrivalForce(Target* target, float radius = def_radius);

	ArrivalForce(const ArrivalForce& other);

	ArrivalForce& operator=(const ArrivalForce& other);

	virtual ~ArrivalForce();

	void setTarget(Target* target);

	virtual glm::vec2 getForce(Agent* agent);

protected:
	Target* m_target;
	float m_radius;
};