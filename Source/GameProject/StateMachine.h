#pragma once
#include "stdafx.h"
#include "State.h"
#include "Entity.h"
#include "Transition.h"

template <typename S> class State;

template <typename S>
class StateMachine {
public:
	StateMachine() {

	};

	//TODO copy, copy assignment
	virtual ~StateMachine() {};

	bool addState(int id, std::shared_ptr<State<S>> newState) {
		bool success = m_states.insert(std::make_pair(id, newState)).second;
		return success;
	}

	void addTransition(std::shared_ptr<Transition<S>> transition) {
		m_fromAnyTransitions.push_back(transition);
	}

	void forceState(int id, S entity) {
		// If going to same state, no transition
		if (!m_currentState || m_currentID != id) {
			m_currentID = id;
			std::shared_ptr<State<S>> newState;
			//Throws exception if id doesn't exist
			try {
				newState = m_states.at(id);
			}
			catch (const std::out_of_range& e) {
				throw std::out_of_range("No state with given id exists in state machine");
			}
			if (m_currentState) {
				m_currentState->onExit(entity);
			}
			newState->onEnter(entity);
			m_currentState = newState;
		}
	}

	void update(S entity, float deltaTime) {
		//TODO exception instead?
		assert(m_currentState);	//Assert current state not null
								//Check transitions from any state
		for (std::shared_ptr<Transition<S>> transition : m_fromAnyTransitions) {
			if (transition->isConditionMet(entity)) {
				int id = transition->getTargetID();
				if (!m_currentState || m_currentID != id) {
					forceState(id, entity);
					break;
				}
			}
		}
		// Update current state
		m_currentState->update(entity, this, deltaTime);
	}

	std::shared_ptr<State<S>> getState() {
		return m_currentState;
	}

protected:
	int m_currentID;
	std::shared_ptr<State<S>> m_currentState;
	std::map<int, std::shared_ptr<State<S>>> m_states;
	std::vector<std::shared_ptr<Transition<S>>> m_fromAnyTransitions;
};