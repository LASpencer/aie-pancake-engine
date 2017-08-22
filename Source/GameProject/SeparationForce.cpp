#include "stdafx.h"
#include "SeparationForce.h"
#include "Agent.h"
#include "VehicleAgent.h"

SeparationForce::SeparationForce(bool fleeEnemies) : m_fleeEnemies(fleeEnemies)
{
}

SeparationForce::~SeparationForce()
{
}

glm::vec2 SeparationForce::getForce(Agent * agent)
{
	glm::vec2 seperatingForce(0);
	VehicleAgent* vehicle = dynamic_cast<VehicleAgent*>(agent);
	if (vehicle != nullptr) {
		glm::vec2 position = agent->getPosition();
		std::vector<VehicleAgent*>& neighbours = (m_fleeEnemies ? vehicle->getEnemyNeighbours() : vehicle->getNeighbours());
		for (auto neighbour : neighbours) {
			seperatingForce += position - neighbour->getPosition();
		}
		if (neighbours.size() > 0) {
			seperatingForce *= 1.f / neighbours.size();
		}
	}
	//gets direction from each neighbor to self, divide by size of neighbourhood, use as target velocity
	return seperatingForce - agent->getVelocity();
}

void SeparationForce::setFleeEnemies(bool fleeEnemies)
{
	m_fleeEnemies = fleeEnemies;
}