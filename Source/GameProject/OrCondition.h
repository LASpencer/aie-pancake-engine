#pragma once
#include "BinaryCondition.h"

template <typename E>
class OrCondition : public BinaryCondition<E> {
public:
	OrCondition();
	OrCondition(std::shared_ptr<Condition<E>> first, std::shared_ptr<Condition<E>> second);
	virtual ~OrCondition();


	virtual bool test(std::shared_ptr<E> entity);

protected:
	std::shared_ptr<Condition<E>> m_first;
	std::shared_ptr<Condition<E>> m_second;
};