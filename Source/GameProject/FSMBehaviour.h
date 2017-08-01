#pragma once
#include "Behaviour.h"
#include "StateMachine.h"

class FSMBehaviour :
	public Behaviour
{
public:
	FSMBehaviour();
	FSMBehaviour(StateMachine<Agent*>* stateMachine);

	virtual ~FSMBehaviour();

	virtual bool update(Agent* agent, float deltaTime);

	void setStateMachine(StateMachine<Agent*>* stateMachine);

	StateMachine<Agent*>* getStateMachine();

protected:
	StateMachine<Agent*>* m_stateMachine;	//HACK should probably be unique ptr
};