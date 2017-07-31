#pragma once
#include "StateMachine.h"
#include "Agent.h"
#include "Target.h"
#include "Transition.h"
#include "TargetInRangeCondition.h"
#include "TimerCondition.h"
#include "NotCondition.h"
//TODO chasey state machine

//class ChaseyStateMachine : public StateMachine<Agent*>
//{
//public:
//	static const float caught_range;
//	static const float wait_time;
//
//	enum stateID {
//		idle,
//		chase,
//		flee
//	};
//
//	ChaseyStateMachine();
//
//	//TODO set target
//
//private:
//	std::shared_ptr<TargetInRangeCondition> m_targetCaught;
//	std::shared_ptr<TimerCondition> m_waitTime;
//
//	EntityTargetPtr m_target;
//
//	void Init();
//};