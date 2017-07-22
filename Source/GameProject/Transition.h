#pragma once
#include "stdafx.h"
#include "Entity.h"

template <typename S> class Condition;

template <typename S>
class Transition {
public:
	Transition(std::shared_ptr<Condition<S>> condition, int targetID) :
		m_condition(condition), m_targetID(targetID)
	{}

	bool isConditionMet(std::shared_ptr<S> entity);

	int getTargetID() const;

private:
	std::shared_ptr<Condition<S>> m_condition;
	int m_targetID;
};