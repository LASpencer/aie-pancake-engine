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
	std::vector<BehaviourPtr> clonedChildren;
	Behaviour* ongoingChild;
	for (BehaviourPtr child : m_children) {
		BehaviourPtr childClone(child->clone());
		clonedChildren.push_back(childClone);
		if (m_ongoingBehaviour->get() == child.get()) {
			ongoingChild = childClone.get();
		}
	}
	SequenceBehaviour* cloned = new SequenceBehaviour(clonedChildren);
	if (m_running) {
		cloned->m_running = true;
		for (std::vector<BehaviourPtr>::iterator it = cloned->m_children.begin(); it != cloned->m_children.end(); ++it) {
			if (it->get() == ongoingChild) {
				cloned->m_ongoingBehaviour = it;
				break;
			}
		}
	}
	return cloned;
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