#pragma once
#include "Behaviour.h"
#include "Target.h"

class TargetInRangeQuestion : public Behaviour {
public:
	TargetInRangeQuestion();
	TargetInRangeQuestion(TargetPtr target, float range);

	virtual ~TargetInRangeQuestion();

	virtual Behaviour* clone();

	virtual BehaviourResult update(Agent* agent, float deltaTime);

	void setTarget(TargetPtr target) { m_target = target; };

	void setRange(float range) { m_range = range; };

private:
	TargetPtr m_target;
	float m_range;
};