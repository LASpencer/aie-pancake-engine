#pragma once
#include "Behaviour.h"
#include "MapGraph.h"
#include "ArrivalForce.h"

class PathfindingBehaviour :
	public Behaviour
{
public:
	PathfindingBehaviour();

	PathfindingBehaviour(const PathfindingBehaviour& other);

	virtual ~PathfindingBehaviour();

	virtual Behaviour* clone();

	virtual BehaviourResult update(Agent* agent, float deltaTime);
};