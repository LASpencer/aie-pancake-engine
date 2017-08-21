#include "stdafx.h"
#include "TargetInRangeQuestion.h"
#include "Agent.h"

TargetInRangeQuestion::TargetInRangeQuestion()
{
}

TargetInRangeQuestion::TargetInRangeQuestion(float range) : m_range(range)
{
}

TargetInRangeQuestion::~TargetInRangeQuestion()
{
}

Behaviour * TargetInRangeQuestion::clone()
{
	return new TargetInRangeQuestion(*this);
}

BehaviourResult TargetInRangeQuestion::update(Agent * agent, float deltaTime)
{
	EntityPtr entity(agent->getEntity());
	glm::vec2 ownPosition = agent->getPosition();
	glm::vec2 distance = ownPosition - agent->getTarget()->getPosition();
	if (glm::dot(distance, distance) < m_range * m_range) {
		return success;
	} else {
		return failure;
	}
}
