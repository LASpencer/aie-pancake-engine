#include "stdafx_test.h"
#include "FooState.h"



FooState::FooState()
{
}


FooState::~FooState()
{
}

void FooState::onEnter()
{
	State::onEnter();
	value = 1;
}

void FooState::onExit()
{
	State::onExit();
	value = 0;
}

int FooState::getValue()
{
	return value;
}

void FooState::update(float deltaTime)
{
	++value;
	if (value == 5) {
		m_shouldTransition = true;
		m_target = 2;
	}
}
