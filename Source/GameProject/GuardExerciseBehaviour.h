#pragma once
#include "SequenceBehaviour.h"
#include "SelectorBehaviour.h"
#include "AttackTarget.h"
#include "Wander.h"
#include "MoveToTarget.h"
#include "TargetInRangeQuestion.h"
#include "Target.h"

class GuardExerciseBehaviour : public SelectorBehaviour {
public:
	GuardExerciseBehaviour();
	GuardExerciseBehaviour(TargetPtr target);
	virtual ~GuardExerciseBehaviour();

	virtual Behaviour* clone();

	virtual BehaviourResult update(Agent* agent, float deltaTime);

	void setTarget(TargetPtr target);

protected:
	std::shared_ptr<AttackTarget> m_attack;
	std::shared_ptr<MoveToTarget> m_move;
	std::shared_ptr<Wander> m_wander;
	std::shared_ptr<TargetInRangeQuestion> m_attackRange;
	std::shared_ptr<TargetInRangeQuestion> m_pursueRange;

	void Init();
};