#include "stdafx.h"
#include "OrCondition.h"

template <typename E>
OrCondition<E>::OrCondition() : BinaryCondition<E>()
{
}

template <typename E>
OrCondition<E>::OrCondition(std::shared_ptr<Condition<E>> first, std::shared_ptr<Condition<E>> second)
	: BinaryCondition<E>(first, second)
{
}

template <typename E>
OrCondition<E>::~OrCondition()
{
}

template<typename E>
bool OrCondition<E>::test(std::shared_ptr<E> entity)
{
	return (m_first && m_first->test(entity)) || (m_second && m_second->test(entity));
}

