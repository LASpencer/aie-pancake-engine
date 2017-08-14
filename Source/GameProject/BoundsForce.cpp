#include "stdafx.h"
#include "BoundsForce.h"
#include "GameProjectApp.h"
#include "Agent.h"

BoundsForce::BoundsForce() : m_minX(0.f), m_minY(0.f), m_maxX(GameProjectApp::max_corner.x), m_maxY(GameProjectApp::max_corner.y)
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
	if (position.y < m_minY) {
		force += glm::vec2(0, 1);
	}
	if (position.y > m_maxY) {
		force += glm::vec2(0, -1);
	}
	if (force != glm::vec2(0)) {
		return agent->getMaxForce() * glm::normalize(force);
	} else {
		return glm::vec2(0);
	}
}
