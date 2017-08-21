#pragma once
#include "Component.h"
#include "Observer.h"
#include "Behaviour.h"
#include "SteeringForce.h"
#include "GameTimer.h"
#include "Grid.h"


class Agent;
typedef std::shared_ptr<Agent> AgentPtr;
typedef std::weak_ptr<Agent> AgentWeakPtr;

class BoundsForce;
typedef std::shared_ptr<BoundsForce> BoundsForcePtr;

class SeekForce;
typedef std::shared_ptr<SeekForce> SeekForcePtr;

class AvoidTerrainForce;
typedef std::shared_ptr<AvoidTerrainForce> AvoidTerrainForcePtr;

class PursueForce;
typedef std::shared_ptr<PursueForce> PursueForcePtr;

struct WeightedForce {
	SteeringForcePtr force;
	float weight;
};

class Agent 
	: public Component, public Observer {
public:
	static const float def_max_velocity;
	static const float def_max_force;
	static const float def_size;

	enum TimerID {
		idle,
		immobile,
		dead
	};

	Agent();
	Agent(float maxVelocity, float maxForce = def_max_force, float size = def_size);
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

	// Returns Agent identifier
	virtual Identifier getID();

	void setMaxVelocity(float maxVelocity);
	void setMaxForce(float maxForce);
	void setSize(float size);

	float getMaxVelocity() { return m_adjustedMaxVelocity; };

	float getMaxForce() { return m_maxForce; };

	float getSize() { return m_size; };

	GameTimer& getTimer(TimerID id);

	glm::vec2 getPosition();

	GridSquarePtr getSquare();

	void setTarget(AgentPtr target);

	AgentPtr getTarget();

	virtual void setBehaviour(BehaviourPtr behaviour);

	/** Sets goal position and calculates path to reach it
	*	Returns true if path found, false if not reachable*/
	virtual bool setGoal(glm::vec2 goal);

	// Agent actions
	// Call these from behaviours to make the agent do things
	
	// Make agent follow its path to the goal
	virtual void followPath(float weight = 1.f);

	bool pursueTarget(float weight = 1.f);

	// Try to match target's velocity
	void matchTargetVelocity(float weight = 1.f);

	void stop(float weight = 1.f);

	// Observer methods
	// Inform observer of event that occurred
	virtual void notify(Subject* subject, EventBase* event);

	// Return true if observer can follow subject
	virtual bool addSubject(Subject* subject);

	// Perform any cleanup needed when removing subject
	virtual void removeSubject(Subject* subject);

	bool canMove();

protected:
	BehaviourPtr m_behaviour;
	std::vector<WeightedForce> m_steeringForces;
	std::map<TimerID, GameTimer> m_timers;
	GridSquarePtr m_square;

	glm::vec2 m_velocity;
	glm::vec2 m_force;
	float m_maxVelocity, m_adjustedMaxVelocity, m_maxForce, m_size;
	bool m_canMove;

	BoundsForcePtr m_stayInBounds;
	AvoidTerrainForcePtr m_avoidImpassableTerrain;
	PursueForcePtr m_pursueTarget;
	
	std::stack<GridSquarePtr> m_path;	// Squares forming path to goal position
	GridSquarePtr m_goalSquare;
	glm::vec2 m_goal;
	AgentPtr m_target;
};