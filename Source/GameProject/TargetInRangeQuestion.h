#pragma once
#include "Behaviour.h"
#include "Target.h"

class TargetInRangeQuestion : public Behaviour {
public:
	TargetInRangeQuestion();
	TargetInRangeQuestion(float range);

	virtual ~TargetInRangeQuestion();

	virtual Behaviour* clone();

	virtual BehaviourResult update(Agent* agent, float deltaTime);

	void setRange(float range) { m_range = range; };

private:
	float m_range;
};