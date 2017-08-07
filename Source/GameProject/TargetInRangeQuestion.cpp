#include "stdafx.h"
#include "TargetInRangeQuestion.h"

TargetInRangeQuestion::TargetInRangeQuestion()
{
}

TargetInRangeQuestion::TargetInRangeQuestion(TargetPtr target, float range) : m_range(range), m_target(target)
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
	glm::vec2 ownPosition = glm::vec2(entity->getPosition()->getGlobalTransform()[2]);
	glm::vec2 distance = ownPosition - m_target->getPosition();
	if (glm::dot(distance, distance) < m_range * m_range) {
		return success;
	} else {
		return failure;
	}
}
