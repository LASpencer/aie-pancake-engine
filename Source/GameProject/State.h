#pragma once
#include "stdafx.h"
#include "Entity.h"


template <typename S> class Transition;
template <typename S> class Condition;
template <typename S> class StateMachine;

template <typename S>
class State {
public:
	State() {};

	virtual ~State() {};

	virtual State* clone() const = 0;

	// Called when transitioning to the state
	virtual void onEnter(S entity) = 0;

	// Called when transitioning from the state
	virtual void onExit(S entity) = 0;

	virtual void update(S entity, StateMachine<S>* sm, float deltaTime);

	/** Add a transition to another state
	* @param transition object defining conditions of transition and key of next state*/
	void addTransition(std::shared_ptr<Transition<S>> transition);

	// Check if any transition should occur and if so do it
	void tryTransitions(S entity, StateMachine<S>* sm);

protected:
	std::vector<std::shared_ptr<Transition<S>>> m_transitions;
};