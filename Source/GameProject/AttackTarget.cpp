#include "stdafx.h"
#include "AttackTarget.h"
#include "imgui.h"

AttackTarget::AttackTarget() : m_force(std::make_shared<PursueForce>())
{
}

AttackTarget::AttackTarget(TargetPtr target) : m_force(std::make_shared<PursueForce>(target))
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
	entity->addForce(std::dynamic_pointer_cast<SteeringForce>(m_force),1.f);

	ImGui::Text("Attack Target behaviour");

	return success;
}

void AttackTarget::setTarget(TargetPtr target)
{
	m_force->setTarget(target);
}
