#include "stdafx.h"
#include "AlignmentForce.h"
#include "Agent.h"
#include "VehicleAgent.h"

AlignmentForce::AlignmentForce()
{
}

AlignmentForce::~AlignmentForce()
{
}

glm::vec2 AlignmentForce::getForce(Agent * agent)
{
	glm::vec2 targetVelocity(0);
	VehicleAgent* vehicle = dynamic_cast<VehicleAgent*>(agent);
	if (vehicle != nullptr) {
		for (auto neighbour : vehicle->getNeighbours()) {
			targetVelocity += neighbour->getVelocity();
		}
		size_t totalNeighbours = vehicle->getNeighbours().size();
		if (totalNeighbours != 0) {
			targetVelocity /= totalNeighbours;
		}
		else {
			// If no neighbours, return no force
			return glm::vec2(0);
		}
	}
	return targetVelocity - agent->getVelocity();
}

