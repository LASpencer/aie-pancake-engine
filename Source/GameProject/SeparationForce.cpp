#include "stdafx.h"
#include "SeparationForce.h"
#include "Agent.h"

SeparationForce::SeparationForce()
{
}

SeparationForce::~SeparationForce()
{
}

glm::vec2 SeparationForce::getForce(Agent * agent)
{
	//gets direction from each neighbor to self, divide by size of neighbourhood, use as target velocity
	glm::vec2 seperatingForce(0);
	glm::vec2 position = agent->getPosition();
	for (auto neighbour : m_neighbours) {
		seperatingForce += position - neighbour.lock()->getPosition();
	}
	seperatingForce *= 1.f / m_neighbours.size();
	return seperatingForce - agent->getVelocity();
}

void SeparationForce::setNeighbours(std::vector<AgentWeakPtr>& neighbours)
{
	m_neighbours = neighbours;
}
