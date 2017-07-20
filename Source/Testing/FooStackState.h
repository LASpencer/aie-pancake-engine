#pragma once
#include "State.h"

class FooStackState :
	public StackState
{
public:
	FooStackState();
	virtual ~FooStackState();


	virtual void onEnter();
	virtual void onExit();

	virtual int getValue();

	virtual void update(float deltaTime);

	virtual void draw(aie::Renderer2D* renderer) {};

protected:
	int value;
};

class BarStackState :
	public FooStackState
{
public:
	BarStackState();
	virtual ~BarStackState();

	virtual void onEnter();
	virtual void onExit();

	virtual void update(float deltaTime);
};