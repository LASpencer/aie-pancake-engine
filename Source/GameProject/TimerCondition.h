#pragma once
#include "Condition.h"

class Agent;

class TimerCondition :
	public Condition<Agent*>
{
public:
	TimerCondition();
	TimerCondition(float time);
	~TimerCondition();

	void setTime(float time) { m_time = time; };

	virtual bool test(Agent* agent);

private:
	float m_time;
};

