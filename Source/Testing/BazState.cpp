#include "stdafx_test.h"
#include "BazState.h"


BazState::BazState()
{
}


BazState::~BazState()
{
}

void BazState::onEnter()
{
	State::onEnter();
	value = 50;
}

void BazState::onExit()
{
	State::onExit();
	value = 0;
}

void BazState::update(float deltaTime)
{
	++value;
}
