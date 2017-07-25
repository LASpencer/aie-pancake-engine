#pragma once
#include "stdafx.h"
#include "Entity.h"
#include "Transition.h"
#include "StateMachine.h"

template <typename S> class Transition;
template <typename S> class Condition;
template <typename S> class StateMachine;

template <typename S>
class State {
public:
	State() {};

	State(const State& other);

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

template<typename S>
State<S>::State(const State & other) : m_transitions(other.m_transitions)
{
}

template <typename S>
void State<S>::update(S entity, StateMachine<S>* sm, float deltaTime)
{
	tryTransitions(entity, sm);
}

template <typename S>
void State<S>::addTransition(std::shared_ptr<Transition<S>> transition)
{
	m_transitions.push_back(transition);
}

template<typename S>
void State<S>::tryTransitions(S entity, StateMachine<S>* sm)
{
	for (std::shared_ptr<Transition<S>> transition : m_transitions) {
		if (transition->isConditionMet(entity)) {
			sm->forceState(transition->getTargetID(), entity);
			break;
		}
	}
}