#include "stdafx.h"
#include "OutnumberedQuestion.h"

OutnumberedQuestion::OutnumberedQuestion()
{
}

OutnumberedQuestion::~OutnumberedQuestion()
{
}

Behaviour * OutnumberedQuestion::clone()
{
	return new OutnumberedQuestion(*this);
}

BehaviourResult OutnumberedQuestion::update(Agent * agent, float deltaTime)
{
	VehicleAgent* vehicle = dynamic_cast<VehicleAgent*>(agent);
	if (vehicle == nullptr) {
		return failure;
	}
	else {
		int friendCount = 0;
		int foeCount = 0;
		if (vehicle->isAlive() && vehicle->canShoot()) {
			friendCount = 1;
		}

		// Add friendly combatants
		for (VehicleAgent* friendTank : vehicle->getNeighbours()) {
			if (friendTank->isAlive() && friendTank->canShoot()) {
				++friendCount;
			}
		}
		// Add enemy combatants
		for (VehicleAgent* foeTank : vehicle->getEnemyNeighbours()) {
			if (foeTank->isAlive() && foeTank->canShoot()) {
				++foeCount;
			}
		}

		if (foeCount > friendCount * 1.5f) {
			return success;
		}
		else {
			return failure;
		}
	}
}