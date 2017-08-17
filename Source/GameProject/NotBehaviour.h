#pragma once
#pragma once
#include "Behaviour.h"

class NotBehaviour : public Behaviour {
	NotBehaviour();

	NotBehaviour(BehaviourPtr behaviour);

	virtual ~NotBehaviour();

	virtual Behaviour* clone();

	virtual BehaviourResult update(Agent* agent, float deltaTime);

	void setBehaviour(BehaviourPtr behaviour);

	BehaviourPtr getBehaviour();

protected:
	BehaviourPtr m_behaviour;
};