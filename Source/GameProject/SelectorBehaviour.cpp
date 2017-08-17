#include "stdafx.h"
#include "SelectorBehaviour.h"

SelectorBehaviour::SelectorBehaviour() : CompositeBehaviour()
{
}

SelectorBehaviour::SelectorBehaviour(std::vector<BehaviourPtr> children) : CompositeBehaviour(children)
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
	std::vector<BehaviourPtr>::iterator child;
	if (m_running) {
		child = m_ongoingBehaviour;
	}
	else {
		child = m_children.begin();
	}
	while(child != m_children.end()) {
		switch ((*child)->update(agent, deltaTime)) {
		case(success) :
			m_running = false;
			return success;
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
	return failure;
}
