#include "stdafx.h"
#include "AlignmentForce.h"

AlignmentForce::~AlignmentForce()
{
}

glm::vec2 AlignmentForce::getForce(Agent * agent)
{
	glm::vec2 targetVelocity(0);
	for (auto neighbour : m_neighbours) {
		targetVelocity += neighbour.lock()->getVelocity();
	}
	targetVelocity /= m_neighbours.size();
	return targetVelocity - agent->getVelocity();
}

void AlignmentForce::setNeighbours(std::vector<AgentWeakPtr>& neighbours)
{
	m_neighbours = neighbours;
}
