#pragma once
#include "SteeringForce.h"

class SeparationForce : public SteeringForce {
	
	SeparationForce();

	virtual glm::vec2 getForce(Agent* agent);
	void setNeighbours(std::vector<AgentWeakPtr>& neighbours);

protected:
	std::vector<AgentWeakPtr> m_neighbours;
};