#pragma once
#include "FooState.h"
class BazState :
	public FooState
{
public:
	BazState();
	virtual ~BazState();

	virtual void onEnter();
	virtual void onExit();

	virtual void update(float deltaTime);
};

