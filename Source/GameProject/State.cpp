#include "stdafx.h"
#include "State.h"
#include "Transition.h"

template <typename S>
void State<S>::update(std::shared_ptr<S> entity, StateMachine<S>* sm)
{
}

template <typename S>
void State<S>::addTransition(std::shared_ptr<Transition<S>> transition)
{
	m_transitions.push_back(transition);
}

template<typename S>
void State<S>::tryTransitions(std::shared_ptr<S> entity, StateMachine<S>* sm)
{
	for (std::shared_ptr<Transition<S>> transition : m_transitions) {
		if (transition->isConditionMet(entity)) {
			sm->forceState(transition->getTargetID());
			break;
		}
	}
}