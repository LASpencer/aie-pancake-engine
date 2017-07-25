#pragma once
#include "BinaryCondition.h"

template <typename E>
class OrCondition : public BinaryCondition<E> {
public:
	OrCondition();
	OrCondition(std::shared_ptr<Condition<E>> first, std::shared_ptr<Condition<E>> second);
	virtual ~OrCondition();


	virtual bool test(E entity);

protected:
	std::shared_ptr<Condition<E>> m_first;
	std::shared_ptr<Condition<E>> m_second;
};

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
bool OrCondition<E>::test(E entity)
{
	return (m_first && m_first->test(entity)) || (m_second && m_second->test(entity));
}

