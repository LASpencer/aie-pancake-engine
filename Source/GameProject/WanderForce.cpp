#include "stdafx.h"
#include "WanderForce.h"

const float WanderForce::def_radius = 100.f;
const float WanderForce::def_jitter = 50.f;
const float WanderForce::def_distance = 200.f;

WanderForce::WanderForce() : m_radius(def_radius), m_jitter(def_jitter), m_distance(def_distance)
{
	float angle = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 6.28318f));
	m_target = glm::vec2(cos(angle), sin(angle)) * m_jitter;
}

WanderForce::WanderForce(float radius, float jitter, float distance) : m_radius(radius), m_jitter(jitter), m_distance(distance)
{
	float angle = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 6.28318f));
	m_target = glm::vec2(cos(angle), sin(angle)) * m_jitter;
}

void WanderForce::setRadius(float radius)
{
	m_radius = abs(radius);
}

void WanderForce::setJitter(float jitter)
{
	m_jitter = abs(jitter);
}

void WanderForce::setDistance(float distance)
{
	m_distance = abs(distance);
}

glm::vec2 WanderForce::getForce(Agent * agent)
{
	float angle = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 6.28318f));
	glm::vec2 jitterVector = glm::vec2(cos(angle), sin(angle)) * m_jitter;
	m_target = m_radius * glm::normalize(m_target + jitterVector);
	glm::vec2 goal = m_target;
	if (agent->getVelocity() != glm::vec2(0)) {
		goal = m_distance * glm::normalize(agent->getVelocity()) + m_target;
	}
	goal += agent->getPosition();
	return seekPoint(agent, goal);
}
