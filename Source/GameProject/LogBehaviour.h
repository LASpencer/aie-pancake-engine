#pragma once
#pragma once
#include "Behaviour.h"
#include "GameProjectApp.h"

// Adds a line of text to an imgui window when the behaviour returns
// Colour of text indicates the result
class LogBehaviour : public Behaviour {
public:
	LogBehaviour(GameProjectApp* app, BehaviourPtr behaviour, std::string message);

	virtual ~LogBehaviour();

	virtual Behaviour* clone();

	// Updates the behaviour, and adds a message to an imgui window
	virtual BehaviourResult update(Agent* agent, float deltaTime);

	void setBehaviour(BehaviourPtr behaviour);

	BehaviourPtr getBehaviour();

	void setMessage(std::string message);

protected:
	BehaviourPtr m_behaviour;
	std::string m_message;
	GameProjectApp* m_app;
};