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
		// Get either friendly or enemy neighbours
		std::vector<VehicleAgent*>& neighbours = (m_fleeEnemies ? vehicle->getEnemyNeighbours() : vehicle->getNeighbours());
		// Apply repulsion from each neighbour
		for (auto neighbour : neighbours) {
			seperatingForce += position - neighbour->getPosition();
		}
		if (neighbours.size() > 0) {
			seperatingForce /= neighbours.size();
		}
		else {
			return glm::vec2(0);
		}
	}
	//gets direction from each neighbor to self, divide by size of neighbourhood, use as target velocity
	return seperatingForce - agent->getVelocity();
}

void SeparationForce::setFleeEnemies(bool fleeEnemies)
{
	m_fleeEnemies = fleeEnemies;
}