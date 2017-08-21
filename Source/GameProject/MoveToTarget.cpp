#include "stdafx.h"
#include "MoveToTarget.h"
#include "imgui.h"
//
//
//MoveToTarget::MoveToTarget() : m_force(std::make_shared<PursueForce>())
//{
//}
//
//MoveToTarget::MoveToTarget(TargetPtr target) : m_force(std::make_shared<PursueForce>(target))
//{
//}
//
//MoveToTarget::~MoveToTarget()
//{
//}
//
//Behaviour * MoveToTarget::clone()
//{
//	return new MoveToTarget(*this);
//}
//
//BehaviourResult MoveToTarget::update(Agent * agent, float deltaTime)
//{
//	agent->addForce(m_force, 1.f);
//
//	ImGui::Text("Move To Target behaviour");
//
//	return success;
//}
//
//void MoveToTarget::setTarget(TargetPtr target)
//{
//	m_force->setTarget(target);
//}
