#pragma once
#include "Condition.h"
#include "Target.h"

class Agent;

class TargetInRangeCondition :
	public Condition<Agent*>
{
public:
	TargetInRangeCondition();
	TargetInRangeCondition(Target* target, float range);

	//TODO copy ctor clones m_target
	~TargetInRangeCondition();

	void setTarget(Target* target) { m_target = target->clone(); };

	void setRange(float range) { m_range = range; };

	virtual bool test(Agent* agent);

private:
	Target* m_target;
	float m_range;
};

