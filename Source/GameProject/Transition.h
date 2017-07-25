#pragma once
#include "stdafx.h"
#include "Entity.h"
#include "Condition.h"

template <typename S> class Condition;

template <typename S>
class Transition {
public:
	Transition(std::shared_ptr<Condition<S>> condition, int targetID) :
		m_condition(condition), m_targetID(targetID)
	{};

	bool isConditionMet(S entity);

	int getTargetID() const;

private:
	std::shared_ptr<Condition<S>> m_condition;
	int m_targetID;
};

template <typename S>
bool Transition<S>::isConditionMet(S entity)
{
	return m_condition->test(entity);
}

template <typename S>
int Transition<S>::getTargetID() const
{
	return m_targetID;
}
