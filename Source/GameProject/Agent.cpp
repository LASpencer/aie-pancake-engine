#include "stdafx.h"
#include "Agent.h"

Agent::Agent() : Component()
{
}

Agent::~Agent()
{
}

Agent::Identifier Agent::getID()
{
	return agent;
}
