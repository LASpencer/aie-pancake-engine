#include "stdafx.h"
#include "MatchVelocityForce.h"
#include "Agent.h"

MatchVelocityForce::MatchVelocityForce()
{
}

MatchVelocityForce::~MatchVelocityForce()
{
}

glm::vec2 MatchVelocityForce::getForce(Agent * agent)
{
	AgentPtr target = agent->getTarget();
	glm::vec2 relativeVelocity = agent->getVelocity() - target->getVelocity();
	return -relativeVelocity;
}
