#pragma once
#include "stdafx.h"
#include "Component.h"

class Body;

typedef std::shared_ptr<Body> BodyPtr;
typedef std::weak_ptr<Body>	BodyWeakPtr;

class Body 
	: public Component {
public:
	Body();
	Body(float mass, float drag, glm::vec2 velocity = glm::vec2(0));
	virtual ~Body();

	//TODO methods to alter
	void setVelocity(glm::vec2 velocity);

	// Instantaneous change in velocity
	void applyDeltaV(glm::vec2 deltaV);

	//Instantaneous change in momentum
	void applyImpulse(glm::vec2 impulse);

	//Add force to apply next update
	void addForce(glm::vec2 force);

	void setDrag(float drag);

	// 0 and infinite treates as infinite mass
	void setMass(float mass);

	float getInvMass();

	//TODO update method

	virtual void update(float deltaTime);

	virtual Identifier getID();

protected:
	//mass, velocity, force, drag, friction
	glm::vec2 m_velocity;
	glm::vec2 m_force;
	float m_invmass;
	float m_drag;
};