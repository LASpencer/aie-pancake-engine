#include "stdafx.h"
#include "FleeDanger.h"
#include "VehicleAgent.h"
#include "imgui.h"


FleeDanger::FleeDanger()
{
	m_separation = std::make_shared<SeparationForce>(true);
}

FleeDanger::~FleeDanger()
{
}

Behaviour * FleeDanger::clone()
{
	return new FleeDanger(*this);
}

BehaviourResult FleeDanger::update(Agent * agent, float deltaTime)
{
	
	VehicleAgent* vehicle = dynamic_cast<VehicleAgent*>(agent);
	if (vehicle == nullptr) {
		return failure;
	}
	else {
		agent->addForce(std::dynamic_pointer_cast<SteeringForce>(m_separation), 1.f);
		ImGui::Text("Flee Danger behaviour");
		return success;
	}
}
