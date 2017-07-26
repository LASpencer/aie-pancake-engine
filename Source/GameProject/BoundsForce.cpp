#include "stdafx.h"
#include "BoundsForce.h"

const float BoundsForce::def_max_x = 1280.f;
const float BoundsForce::def_max_y = 720.f;

BoundsForce::BoundsForce() : m_minX(0.f), m_minY(0.f), m_maxX(def_max_x), m_maxY(def_max_y)
{
}

BoundsForce::BoundsForce(float minX, float maxX, float minY, float maxY) : m_minX(minX), m_minY(minY), m_maxX(maxX), m_maxY(maxY)
{
}

BoundsForce::~BoundsForce()
{
}

void BoundsForce::setBounds(float minX, float maxX, float minY, float maxY)
{
	m_minX = minX;
	m_maxX = maxX;
	m_minY = minY;
	m_maxY = maxY;
}

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
