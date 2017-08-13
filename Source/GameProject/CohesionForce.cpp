#include "stdafx.h"
#include "CohesionForce.h"
#include "Agent.h"

CohesionForce::CohesionForce()
{
}

CohesionForce::~CohesionForce()
{
}

glm::vec2 CohesionForce::getForce(Agent * agent)
{
	glm::vec2 avgPos;
	for (auto neighbour : m_neighbours) {
		avgPos += neighbour.lock()->getPosition();
	}
	avgPos /= m_neighbours.size();
	return seekPoint(agent, avgPos);
}

void CohesionForce::setNeighbours(std::vector<AgentWeakPtr>& neighbours)
{
	m_neighbours = neighbours;
}
