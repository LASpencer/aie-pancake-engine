#include "stdafx.h"
#include "MoveToTarget.h"
#include "imgui.h"


MoveToTarget::MoveToTarget() : m_force()
{
}

MoveToTarget::MoveToTarget(TargetPtr target) : m_force(target)
{
}

MoveToTarget::~MoveToTarget()
{
}

Behaviour * MoveToTarget::clone()
{
	return new MoveToTarget(*this);
}

BehaviourResult MoveToTarget::update(Agent * entity, float deltaTime)
{
	entity->addForce(m_force.getForce(entity));

	ImGui::Text("Move To Target behaviour");

	return success;
}

void MoveToTarget::setTarget(TargetPtr target)
{
	m_force.setTarget(target);
}
