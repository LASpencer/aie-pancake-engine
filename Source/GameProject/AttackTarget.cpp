#include "stdafx.h"
#include "AttackTarget.h"
#include "imgui.h"
#include "VehicleAgent.h"

AttackTarget::AttackTarget() : m_force(std::make_shared<PursueForce>())
{
}

AttackTarget::~AttackTarget()
{
}

Behaviour * AttackTarget::clone()
{
	return new AttackTarget();
}

BehaviourResult AttackTarget::update(Agent * agent, float deltaTime)
{
	VehicleAgent* tank = dynamic_cast<VehicleAgent*>(agent);
	if (tank == nullptr || !tank->canShoot()) {
		return failure;
	}
	else {
		//TODO move all these conditionals into own behaviours
		VehiclePtr target = std::dynamic_pointer_cast<VehicleAgent>(agent->getTarget());
		if (target.get() == nullptr) {
			return failure;
		} else if (tank->attack(target)) {
			ImGui::Text("Attack Target behaviour");
		} else{
			return failure;
		}
	}
	return success;
}

