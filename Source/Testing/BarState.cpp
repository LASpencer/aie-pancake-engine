#include "stdafx_test.h"
#include "BarState.h"


BarState::BarState()
{
}


BarState::~BarState()
{
}

void BarState::onEnter()
{
	State::onEnter();
	value = 10;
}

void BarState::onExit()
{
	State::onExit();
	value = 0;
}

void BarState::update(float deltaTime)
{
	--value;
	if (value == 7) {
		m_shouldTransition = true;
		m_target = 1;
	}
}


