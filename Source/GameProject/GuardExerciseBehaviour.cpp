#include "stdafx.h"
#include "GuardExerciseBehaviour.h"
#include "imgui.h"

GuardExerciseBehaviour::GuardExerciseBehaviour()
{
	Init();
}

GuardExerciseBehaviour::GuardExerciseBehaviour(TargetPtr target)
{
	Init();
	setTarget(target);
}

GuardExerciseBehaviour::~GuardExerciseBehaviour()
{
}

Behaviour * GuardExerciseBehaviour::clone()
{
	return new GuardExerciseBehaviour(*this);
}

BehaviourResult GuardExerciseBehaviour::update(Agent * agent, float deltaTime)
{
	ImGui::Begin("Guard Action");
	BehaviourResult result = SelectorBehaviour::update(agent, deltaTime);
	ImGui::End();
	return result;
}

void GuardExerciseBehaviour::setTarget(TargetPtr target)
{
	m_attack->setTarget(target);
	m_move->setTarget(target);
	m_attackRange->setTarget(target);
	m_pursueRange->setTarget(target);
}

void GuardExerciseBehaviour::Init()
{
	m_attack = std::make_shared<AttackTarget>();
	m_move = std::make_shared<MoveToTarget>();
	m_wander = std::make_shared<Wander>();

	m_attackRange = std::make_shared<TargetInRangeQuestion>();
	m_pursueRange = std::make_shared<TargetInRangeQuestion>();
	m_attackRange->setRange(50.f);
	m_pursueRange->setRange(200.f);
	
	std::shared_ptr<SequenceBehaviour> tryAttacking = std::make_shared<SequenceBehaviour>();
	tryAttacking->addChild(m_attackRange);
	tryAttacking->addChild(m_attack);

	std::shared_ptr<SelectorBehaviour> moveOrAttack = std::make_shared<SelectorBehaviour>();
	moveOrAttack->addChild(tryAttacking);
	moveOrAttack->addChild(m_move);

	std::shared_ptr<SequenceBehaviour> tryPursuit = std::make_shared<SequenceBehaviour>();
	tryPursuit->addChild(m_pursueRange);
	tryPursuit->addChild(moveOrAttack);

	addChild(tryPursuit);
	addChild(m_wander);

}
