#pragma once
#include "Behaviour.h"
#include "Input.h"

class KeyboardControlForce;

class KeyboardController :
	public Behaviour
{
public:
	KeyboardController();
	virtual ~KeyboardController();

	virtual Behaviour* clone();

	virtual BehaviourResult update(Agent* agent, float deltaTime);

protected:
	std::shared_ptr<KeyboardControlForce> m_keyboardControl;
};

