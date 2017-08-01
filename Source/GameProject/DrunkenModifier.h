#pragma once
#include "Behaviour.h"

class DrunkenModifier :
	public Behaviour
{
public:
	DrunkenModifier();
	virtual ~DrunkenModifier();

	virtual BehaviourResult update(Agent* entity, float deltaTime);

private:
	float m_time;
};