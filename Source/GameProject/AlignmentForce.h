#pragma once
#include "SteeringForce.h"

class AlignmentForce : public SteeringForce {
public:
	AlignmentForce();
	virtual ~AlignmentForce();

	virtual glm::vec2 getForce(Agent* agent);
	void setNeighbours(std::vector<AgentWeakPtr>& neighbours);

protected:
	std::vector<AgentWeakPtr> m_neighbours;
};