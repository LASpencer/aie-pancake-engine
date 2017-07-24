#include "stdafx.h"
#include "TargetInRangeCondition.h"


TargetInRangeCondition::TargetInRangeCondition()
{
}

TargetInRangeCondition::TargetInRangeCondition(Target * target, float range) : m_range(range)
{
	m_target = target->clone();
}


TargetInRangeCondition::~TargetInRangeCondition()
{
	delete m_target;
}

bool TargetInRangeCondition::test(Agent * agent)
{
	EntityPtr entity(agent->getEntity());
	glm::vec2 ownPosition = glm::vec2(entity->getPosition()->getGlobalTransform()[2]);
	glm::vec2 distance = ownPosition - m_target->getPosition();
	return (glm::dot(distance, distance) < m_range * m_range);
}
