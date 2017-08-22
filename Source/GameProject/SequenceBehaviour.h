#pragma once
#include "CompositeBehaviour.h"

class SequenceBehaviour : public CompositeBehaviour
{
public:
	SequenceBehaviour();

	SequenceBehaviour(std::vector<BehaviourPtr> children);

	virtual ~SequenceBehaviour();

	virtual Behaviour* clone();

	// Runs all behaviours in order until one fails
	virtual BehaviourResult update(Agent* agent, float deltaTime);
};