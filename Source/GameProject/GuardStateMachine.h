#pragma once
#include "StateMachine.h"
#include "Agent.h"
#include "Target.h"
#include "Transition.h"
#include "TargetInRangeCondition.h"
#include "TimerCondition.h"
#include "NotCondition.h"
//guard state machine class, provides interface to set target, patrol route
//Holds condition instances, so the target and range can be set from here

class GuardStateMachine : public StateMachine<Agent*>
{
public:
	static const float def_near_range;
	static const float def_far_range;
	static const float def_wait_time;

	enum {
		idle,
		patrol,
		attack
	};

	GuardStateMachine();

	//TODO copy, copy assign is deep copy of conditions

	GuardStateMachine(std::vector<glm::vec2> route, EntityPtr target);

	virtual ~GuardStateMachine();

	void setTarget(EntityPtr target);

	void setRoute(std::vector<glm::vec2> route);

	void setNearRange(float near);

	void setFarRange(float far);

	void setWaitTime(float time);

private:
	std::shared_ptr<TargetInRangeCondition> m_targetClose;
	std::shared_ptr<TargetInRangeCondition> m_targetNotFar;
	std::shared_ptr<TimerCondition> m_waitTime;

	EntityTargetPtr m_target;
};