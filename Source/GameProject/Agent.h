#pragma once
#include "Component.h"
#include "Behaviour.h"

class Agent;
typedef std::shared_ptr<Agent> AgentPtr;

class Agent 
	: public Component {
public:
	static const float def_max_velocity;
	static const float def_max_force;

	Agent();
	Agent(float maxVelocity, float maxForce = def_max_force);
	virtual ~Agent();

	void setVelocity(glm::vec2 velocity);

	glm::vec2 getVelocity() { return m_velocity; };

	// Instantaneous change in velocity
	void applyImpulse(glm::vec2 impulse);

	//Add rate of change t
	virtual void addForce(glm::vec2 force);

	virtual void update(float deltaTime);

	// Returns Controller identifier
	virtual Identifier getID();

	void setMaxVelocity(float maxVelocity);
	void setMaxForce(float maxForce);

	void resetTime();

	float getMaxVelocity() { return m_maxVelocity; };

	float getMaxForce() { return m_maxForce; };

	float getTime() { return m_time; };

	void addBehaviour(BehaviourPtr behaviour);

	void setBehaviours(std::vector<BehaviourPtr> behaviours);

protected:
	std::vector<BehaviourPtr> m_behaviours;
	glm::vec2 m_velocity;
	glm::vec2 m_force;
	float m_maxVelocity, m_maxForce, m_time;
};