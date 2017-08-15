#include "stdafx.h"
#include "AgentIsTankQuestion.h"
#include "Entity.h"

AgentIsTankQuestion::AgentIsTankQuestion()
{
}

AgentIsTankQuestion::~AgentIsTankQuestion()
{
}

Behaviour * AgentIsTankQuestion::clone()
{
	return new AgentIsTankQuestion(*this);
}

BehaviourResult AgentIsTankQuestion::update(Agent * agent, float deltaTime)
{
	VehicleAgent* tank = dynamic_cast<VehicleAgent*>(agent);
	int entityTag = agent->getEntity().lock()->getTagMask();
	if (tank != nullptr && (entityTag & Entity::ETag::tank)) {
		return success;
	} else {
		return failure;
	}
}
