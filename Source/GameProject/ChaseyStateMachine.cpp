#include "stdafx.h"
#include "ChaseyStateMachine.h"
#include "GuardStates.h"
#include "ChaseyStates.h"
#include "AndCondition.h"

ChaseyStateMachine::ChaseyStateMachine()
{
	m_targetCaught = std::make_shared<TargetInRangeCondition>(caught_range);
	m_waitTime = std::make_shared<TimerCondition>(wait_time);
	
}

void ChaseyStateMachine::Init()
{
	std::shared_ptr<AndCondition<Agent*>> gotCaught = std::make_shared<AndCondition<Agent*>>(m_targetCaught, m_waitTime);

	std::shared_ptr<Transition<Agent*>> caughtTarget = std::make_shared<Transition<Agent*>>(m_targetCaught, flee);
	std::shared_ptr<Transition<Agent*>> gotCaughtTransition = std::make_shared<Transition<Agent*>>(gotCaught, idle);
	std::shared_ptr<Transition<Agent*>> startChasing = std::make_shared<Transition<Agent*>>(m_waitTime, chase);

	//TODO add states, add conditions to states
}
