#include "stdafx.h"
#include "TimerCondition.h"
#include "Agent.h"

TimerCondition::TimerCondition()
{
}

TimerCondition::TimerCondition(float time) : m_time(time)
{
}


TimerCondition::~TimerCondition()
{
}

bool TimerCondition::test(Agent * agent)
{
	return (agent->getTime()) >= m_time;
}