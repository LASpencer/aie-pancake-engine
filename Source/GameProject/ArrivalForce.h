#pragma once
#include "SteeringForce.h"
#include "Target.h"

class ArrivalForce;
typedef std::shared_ptr<ArrivalForce> ArrivalForcePtr;

class ArrivalForce :
	public SteeringForce
{
public:
	static const float def_radius;

	ArrivalForce();

	ArrivalForce(TargetPtr target, float radius = def_radius);

	ArrivalForce(const ArrivalForce& other);

	ArrivalForce& operator=(const ArrivalForce& other);

	virtual ~ArrivalForce();

	void setTarget(TargetPtr target);

	virtual glm::vec2 getForce(Agent* agent);

protected:
	TargetPtr m_target;
	float m_radius;
};