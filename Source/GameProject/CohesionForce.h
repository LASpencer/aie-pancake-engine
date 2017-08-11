#pragma once
#include "SteeringForce.h"

class CohesionForce : public SteeringForce {
public:
	CohesionForce();
	virtual ~CohesionForce();

	virtual glm::vec2 getForce(Agent* agent);
	void setNeighbours(std::vector<AgentWeakPtr>& neighbours);

protected:
	std::vector<AgentWeakPtr> m_neighbours;
};