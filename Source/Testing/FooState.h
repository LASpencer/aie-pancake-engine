#pragma once
#include "stdafx_test.h"
#include "State.h"

class FooState :
	public State
{
public:
	FooState();
	virtual ~FooState();

	virtual void onEnter();
	virtual void onExit();

	virtual int getValue();

	virtual void update(float deltaTime);

	virtual void draw(aie::Renderer2D* renderer) {};

protected:
	int value;
};

