#pragma once
#include "State.h"
#include "TargetInRangeCondition.h"
#include "Target.h"
#include "SeekForce.h"

class Agent;

//Idle state
class IdleState : State<Agent*>
{
	IdleState();

	IdleState(const IdleState& other);

	virtual ~IdleState();

	virtual State* clone() const;

	virtual void onEnter(Agent* agent);
	virtual void onExit(Agent* agent);
};

//Patrol state
class PatrolState : State<Agent*>
{
	static const float waypoint_size;

	PatrolState();
	PatrolState(std::vector<glm::vec2> route);
	PatrolState(const PatrolState& other);
	virtual ~PatrolState();

	virtual State* clone() const;

	void setRoute(std::vector<glm::vec2> route);

	virtual void onEnter(Agent* agent);

	virtual void onExit(Agent* agent);

	virtual void update(Agent* entity, StateMachine<Agent*>* sm, float deltaTime);

protected:
	std::vector<PointTarget> m_route;
	std::vector<PointTarget>::iterator m_currentWaypoint;
	TargetInRangeCondition m_hasReachedWaypoint;

	SeekForce m_seekWaypoint;

	void incrementWaypoint();

	void startRoute();
};


//Attack state
class AttackState : State<Agent*>
{
	AttackState();
	AttackState(EntityPtr target);
	AttackState(const PatrolState& other);
	virtual ~AttackState();

	virtual State* clone() const;

	void setTarget(EntityPtr target);

	virtual void onEnter(Agent* agent);

	virtual void onExit(Agent* agent);

	virtual void update(Agent* entity, StateMachine<Agent*>* sm, float deltaTime);

protected:
	SeekForce m_attackTarget;
};