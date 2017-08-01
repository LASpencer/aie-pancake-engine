#pragma once
#include "CompositeBehaviour.h"

class SelectorBehaviour: public CompositeBehaviour
{
public:
	SelectorBehaviour();

	SelectorBehaviour(std::vector<BehaviourPtr> children);

	virtual ~SelectorBehaviour();

	virtual Behaviour* clone();

	//Try in order until success
	virtual BehaviourResult update(Agent* agent, float deltaTime);
};