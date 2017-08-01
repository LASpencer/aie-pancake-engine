#pragma once
#include "Behaviour.h"

class CompositeBehaviour : public Behaviour
{
public:
	CompositeBehaviour();

	virtual ~CompositeBehaviour();

	virtual Behaviour* clone() = 0;

protected:
	std::vector<BehaviourPtr> m_childre;
};