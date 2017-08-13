#pragma once
#include "Behaviour.h"
#include "MapGraph.h"
#include "ArrivalForce.h"

class PathfindingBehaviour :
	public Behaviour
{
public:
	PathfindingBehaviour(MapGraph* map, MapNode* startingNode);

	PathfindingBehaviour(const PathfindingBehaviour& other);

	virtual ~PathfindingBehaviour();

	virtual Behaviour* clone();

	virtual BehaviourResult update(Agent* agent, float deltaTime);

private:
	std::stack<glm::vec2> m_path;
	MapGraph* m_map;
	MapNode* m_currentNode;
	PointTargetPtr m_target;

	std::shared_ptr<ArrivalForce> m_arrive;
};