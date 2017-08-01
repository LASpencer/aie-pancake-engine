#include "stdafx.h"
#include "SelectorBehaviour.h"

SelectorBehaviour::SelectorBehaviour() : CompositeBehaviour()
{
}

SelectorBehaviour::SelectorBehaviour(std::vector<BehaviourPtr> children) : SelectorBehaviour(children)
{
}

SelectorBehaviour::~SelectorBehaviour()
{
}

Behaviour * SelectorBehaviour::clone()
{
	return new SelectorBehaviour(*this);
}

BehaviourResult SelectorBehaviour::update(Agent * agent, float deltaTime)
{
	for (BehaviourPtr child : m_children) {
		switch (child->update(agent, deltaTime)) {
		case(success) :
			return success;
			break;
		case(running):
			return running;
			break;
		default:
			break;
		}

	}
	return failure;
}
