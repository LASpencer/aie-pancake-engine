#pragma once
#include "Behaviour.h"
#include "WanderForce.h"

class Wander : public Behaviour {
public:
	Wander();
	Wander(float radius, float jitter, float distance);
	Wander(const Wander& other);


	virtual Behaviour* clone();

	virtual BehaviourResult update(Agent* entity, float deltaTime);

	void setRadius(float radius);

	void setJitter(float jitter);

	void setDistance(float distance);

protected:
	WanderForce m_force;
};