#pragma once
#include "Component.h"
#include "Behaviour.h"


class Agent 
	: public Component {
public:
	static const float def_max_velocity;
	static const float def_max_force;

	Agent();
	Agent(float maxVelocity, float maxForce = def_max_force);
	virtual ~Agent();

	// Returns Controller identifier
	virtual Identifier getID();

	// Tests whether entity is valid owner of this controller
	virtual bool isValidEntity(EntityPtr entity);

	float getMaxVelocity() { return m_maxVelocity; };

	float getMaxForce() { return m_maxForce; };

protected:
	std::vector<BehaviourPtr> m_behaviours;
	float m_maxVelocity, m_maxForce;
};