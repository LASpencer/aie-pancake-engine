#pragma once
#include "Condition.h"
#include "Target.h"

class Agent;

class TargetInRangeCondition :
	public Condition<Agent*>
{
public:
	TargetInRangeCondition();
	TargetInRangeCondition(TargetPtr target, float range);

	//TODO copy ctor clones m_target
	~TargetInRangeCondition();

	void setTarget(TargetPtr target) { m_target = target; };

	void setRange(float range) { m_range = range; };

	virtual bool test(Agent* agent);

private:
	TargetPtr m_target;
	float m_range;
};


