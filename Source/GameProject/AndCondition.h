#pragma once
#include "BinaryCondition.h"

template <typename E>
class AndCondition : public BinaryCondition<E> {
public:
	AndCondition();
	AndCondition(std::shared_ptr<Condition<E>> first, std::shared_ptr<Condition<E>> second);
	virtual ~AndCondition();

	virtual bool test(std::shared_ptr<E> entity);


};