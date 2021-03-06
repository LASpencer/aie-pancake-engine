#include "stdafx.h"
#include "Transition.h"
#include "Condition.h"

template <typename S>
bool Transition<S>::isConditionMet(std::shared_ptr<S> entity)
{
	return m_condition->test(entity);
}

template <typename S>
int Transition<S>::getTargetID() const
{
	return m_targetID;
}
