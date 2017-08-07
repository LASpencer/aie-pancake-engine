#include "stdafx.h"
#include "SequenceBehaviour.h"

SequenceBehaviour::SequenceBehaviour() : CompositeBehaviour()
{
}

SequenceBehaviour::SequenceBehaviour(std::vector<BehaviourPtr> children) : CompositeBehaviour(children)
{
}

SequenceBehaviour::~SequenceBehaviour()
{
}

Behaviour * SequenceBehaviour::clone()
{
	return new SequenceBehaviour(*this);
}


BehaviourResult SequenceBehaviour::update(Agent * agent, float deltaTime)
{
	for (BehaviourPtr child : m_children) {
		switch (child->update(agent, deltaTime)) {
		case(failure):
			return failure;
			break;
		case(running):
			//TODO set running on, ongoing behaviour is child
			return running;
			break;
		default:
			break;
		}
	}
	return success;
}