#pragma once
#include "Behaviour.h"
#include "Input.h"

class KeyboardController :
	public Behaviour
{
public:
	KeyboardController();
	virtual ~KeyboardController();

	virtual void update(Agent* agent, float deltaTime);
};

