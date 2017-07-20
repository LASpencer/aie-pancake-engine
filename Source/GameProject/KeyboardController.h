#pragma once
#include "Behaviour.h"
#include "Input.h"

class KeyboardController :
	public Behaviour
{
public:
	KeyboardController();
	~KeyboardController();

	virtual void update(EntityPtr entity, float deltaTime);
};

