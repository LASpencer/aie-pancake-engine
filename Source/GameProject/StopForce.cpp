#include "stdafx.h"
#include "StopForce.h"

StopForce::StopForce()
{
}

StopForce::~StopForce()
{
}

glm::vec2 StopForce::getForce(Agent * agent)
{
	return -(agent->getVelocity());
}
