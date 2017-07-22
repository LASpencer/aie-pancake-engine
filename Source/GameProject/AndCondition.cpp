#include "stdafx.h"
#include "AndCondition.h"

template <typename E>
AndCondition<E>::AndCondition() : BinaryCondition<E>()
{
}

template <typename E>
AndCondition<E>::AndCondition(std::shared_ptr<Condition<E>> first, std::shared_ptr<Condition<E>> second) : BinaryCondition<E>(first, second)
{
}

template <typename E>
AndCondition<E>::~AndCondition()
{
}


template <typename E>
bool AndCondition<E>::test(std::shared_ptr<E> entity)
{
	return m_first && m_second && m_first->test(entity) && m_second->test(entity);
}
