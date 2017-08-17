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
	std::vector<BehaviourPtr>::iterator child;
	if (m_running) {
		child = m_ongoingBehaviour;
	}
	else {
		child = m_children.begin();
	}
	while (child != m_children.end()) {
		switch ((*child)->update(agent, deltaTime)) {
		case(failure):
			m_running = false;
			return failure;
			break;
		case(running):
			// set running on, ongoing behaviour is child
			m_running = true;
			m_ongoingBehaviour = child;
			return running;
			break;
		default:
			break;
		}
		++child;
	}
	m_running = false;
	return success;
}