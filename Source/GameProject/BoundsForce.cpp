#include "stdafx.h"
#include "BoundsForce.h"

glm::vec2 BoundsForce::getForce(Agent * agent)
{
	glm::vec2 position = agent->getPosition();
	glm::vec2 force(0);
	if (position.x < m_minX) {
		force += glm::vec2(1, 0);
	}
	if (position.x >m_maxX) {
		force += glm::vec2(-1, 0);
	}
	if (position.x < m_minY) {
		force += glm::vec2(0, 1);
	}
	if (position.x > m_maxY) {
		force += glm::vec2(0, -1);
	}
	return agent->getMaxForce() * glm::normalize(force);
}
