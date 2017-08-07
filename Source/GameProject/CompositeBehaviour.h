#pragma once
#include "Behaviour.h"

class CompositeBehaviour : public Behaviour
{
public:
	CompositeBehaviour();

	CompositeBehaviour(const std::vector<BehaviourPtr>& children);

	virtual ~CompositeBehaviour();

	virtual Behaviour* clone() = 0;

	void addChild(BehaviourPtr child);

	void setChildren(const std::vector<BehaviourPtr>& children);

protected:
	std::vector<BehaviourPtr> m_children;
	std::vector<BehaviourPtr>::iterator m_ongoingBehaviour;
	bool m_running;
};