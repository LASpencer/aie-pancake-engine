#pragma once
#include "CompositeBehaviour.h"

class SequenceBehaviour : public CompositeBehaviour
{
public:
	SequenceBehaviour();

	SequenceBehaviour(std::vector<BehaviourPtr> children);

	virtual ~SequenceBehaviour();

	virtual Behaviour* clone();

	//Perform in order until failure
	virtual BehaviourResult update(Agent* agent, float deltaTime);
};