#pragma once
#include "Behaviour.h"
#include "Input.h"

class KeyboardController :
	public Behaviour
{
public:
	KeyboardController();
	virtual ~KeyboardController();

	virtual Behaviour* clone();

	virtual BehaviourResult update(Agent* agent, float deltaTime);
};

