#pragma once
#pragma once
#include "Behaviour.h"

class LogBehaviour : public Behaviour {
public:
	LogBehaviour();

	LogBehaviour(BehaviourPtr behaviour, std::string message);

	virtual ~LogBehaviour();

	virtual Behaviour* clone();

	virtual BehaviourResult update(Agent* agent, float deltaTime);

	void setBehaviour(BehaviourPtr behaviour);

	BehaviourPtr getBehaviour();

	void setMessage(std::string message);

protected:
	BehaviourPtr m_behaviour;
	std::string m_message;
};