#pragma once
#include "Component.h"
#include "Behaviour.h"
#include "SteeringForce.h"
#include "GameTimer.h"
#include "Grid.h"

class Agent;
typedef std::shared_ptr<Agent> AgentPtr;
typedef std::weak_ptr<Agent> AgentWeakPtr;

class BoundsForce;
typedef std::shared_ptr<BoundsForce> BoundsForcePtr;

class AvoidTerrainForce;
typedef std::shared_ptr<AvoidTerrainForce> AvoidTerrainForcePtr;

struct WeightedForce {
	SteeringForcePtr force;
	float weight;
};

class Agent 
	: public Component {
public:
	static const float def_max_velocity;
	static const float def_max_force;

	enum TimerID {
		stuck_in_terrain,
		idle
	};

	Agent();
	Agent(float maxVelocity, float maxForce = def_max_force);
	virtual ~Agent();

	void setVelocity(glm::vec2 velocity);

	glm::vec2 getVelocity() { return m_velocity; };

	// Instantaneous change in velocity
	void applyImpulse(glm::vec2 impulse);

	//TODO: replace with API to enable/disable specific actions
	void addForce(SteeringForcePtr force, float weight);

	// Runs agent behaviours and sets force for this frame
	virtual void update(float deltaTime);

	// Applies force to velocity and moves agent
	virtual void moveAgent(float deltaTime);

	// Returns Controller identifier
	virtual Identifier getID();

	void setMaxVelocity(float maxVelocity);
	void setMaxForce(float maxForce);

	float getMaxVelocity() { return m_adjustedMaxVelocity; };

	float getMaxForce() { return m_maxForce; };

	GameTimer& getTimer(TimerID id);

	glm::vec2 getPosition();

	GridSquarePtr getSquare();

	virtual void setBehaviour(BehaviourPtr behaviour);

protected:
	BehaviourPtr m_behaviour;
	std::vector<WeightedForce> m_steeringForces;
	std::map<TimerID, GameTimer> m_timers;
	GridSquarePtr m_square;
	glm::vec2 m_velocity;
	glm::vec2 m_force;
	float m_maxVelocity, m_adjustedMaxVelocity, m_maxForce;
	BoundsForcePtr m_stayInBounds;
	AvoidTerrainForcePtr m_avoidImpassableTerrain;
};