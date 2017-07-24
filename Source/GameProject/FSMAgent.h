#pragma once
#include "Agent.h"
#include "StateMachine.h"

class FSMAgent :
	public Agent
{
public:
	FSMAgent();

	FSMAgent(float maxVelocity, float maxForce = def_max_force);

	virtual ~FSMAgent();

	virtual void update(float deltaTime);

	virtual void draw(aie::Renderer2D* renderer) {};

	StateMachine<FSMAgent>& getStateMachine();

protected:
	StateMachine<FSMAgent> m_stateMachine;
};

