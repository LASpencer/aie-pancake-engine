#pragma once
#include "ComplexCondition.h"

template <typename E>
class NotCondition : public ComplexCondition<E> {
public:
	NotCondition();
	NotCondition(std::shared_ptr<Condition<E>> condition);
	virtual ~NotCondition();

	// 
	void setCondition(std::shared_ptr<Condition<E>> condition);

	std::shared_ptr<Condition<E>> getCondition();


	//Returns true if test depends on conditions test
	virtual bool isDependentOn(ComplexCondition<E>* condition);

	virtual bool test(std::shared_ptr<E> entity);

protected:
	std::shared_ptr<Condition<E>> m_condition;
};