#pragma once
#include "CompositeBehaviour.h"

class SelectorBehaviour: public CompositeBehaviour
{
public:
	SelectorBehaviour();

	SelectorBehaviour(std::vector<BehaviourPtr> children);

	virtual ~SelectorBehaviour();

	virtual Behaviour* clone();

	// Try each behaviour in order until one succeeds
	virtual BehaviourResult update(Agent* agent, float deltaTime);
};