#pragma once
#include "Behaviour.h"
#include "StateMachine.h"

class FSMBehaviour :
	public Behaviour
{
public:
	FSMBehaviour();
	virtual ~FSMBehaviour();

	virtual void update(Agent* agent, float deltaTime);

	StateMachine<Agent*>& getStateMachine();

protected:
	StateMachine<Agent*> m_stateMachine;
};