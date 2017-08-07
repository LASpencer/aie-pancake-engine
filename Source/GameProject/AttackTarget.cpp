#include "stdafx.h"
#include "AttackTarget.h"
#include "imgui.h"

AttackTarget::AttackTarget() : m_force()
{
}

AttackTarget::AttackTarget(TargetPtr target) : m_force(target)
{
}

AttackTarget::~AttackTarget()
{
}

Behaviour * AttackTarget::clone()
{
	return new AttackTarget();
}

BehaviourResult AttackTarget::update(Agent * entity, float deltaTime)
{
	entity->addForce(m_force.getForce(entity));

	ImGui::Text("Attack Target behaviour");

	return success;
}

void AttackTarget::setTarget(TargetPtr target)
{
	m_force.setTarget(target);
}
