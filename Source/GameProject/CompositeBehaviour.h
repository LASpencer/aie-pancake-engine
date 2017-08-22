#pragma once
#include "Behaviour.h"

// Base class for behaviours made up of other behaviours
class CompositeBehaviour : public Behaviour
{
public:
	CompositeBehaviour();

	CompositeBehaviour(const std::vector<BehaviourPtr>& children);

	virtual ~CompositeBehaviour();

	virtual Behaviour* clone() = 0;

	// Adds new child behaviour to end of children
	void addChild(BehaviourPtr child);

	// Sets
	void setChildren(const std::vector<BehaviourPtr>& children);

protected:
	std::vector<BehaviourPtr> m_children;
	std::vector<BehaviourPtr>::iterator m_ongoingBehaviour;		// Running behaviour
	bool m_running;		// True if a behavior returned running last frame
};