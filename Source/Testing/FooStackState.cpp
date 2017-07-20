#include "stdafx_test.h"
#include "FooStackState.h"
#include "State.h"


FooStackState::FooStackState()
{
}


FooStackState::~FooStackState()
{
}

void FooStackState::onEnter()
{
	StackState::onEnter();
	value = 1;
}

void FooStackState::onExit()
{
	StackState::onExit();
	value = 0;
}


int FooStackState::getValue()
{
	return value;
}

void FooStackState::update(float deltaTime)
{
	++value;
	if (m_focus) {
		value += 10;
	}
}

BarStackState::BarStackState() : FooStackState()
{
}

BarStackState::~BarStackState()
{
}


void BarStackState::onEnter()
{
	StackState::onEnter();
	value = 100;
}

void BarStackState::onExit()
{
	StackState::onExit();
	value = 0;
}

void BarStackState::update(float deltaTime)
{
	++value;
	if (m_focus) {
		value -= 10;
	}
}
