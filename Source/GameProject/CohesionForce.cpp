#include "stdafx.h"
#include "CohesionForce.h"
#include "Agent.h"
#include "VehicleAgent.h"

CohesionForce::CohesionForce()
{
}

CohesionForce::~CohesionForce()
{
}

glm::vec2 CohesionForce::getForce(Agent * agent)
{
	glm::vec2 avgPos;
	VehicleAgent* vehicle = dynamic_cast<VehicleAgent*>(agent);
	if (vehicle != nullptr) {
		for (auto neighbour : vehicle->getNeighbours()) {
			avgPos += neighbour->getPosition();
		}
		size_t totalNeighbours = vehicle->getNeighbours().size();
		if (totalNeighbours != 0) {
			avgPos /= totalNeighbours;
		}
	}
	return seekPoint(agent, avgPos);
}