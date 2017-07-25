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

	virtual bool test(E entity);

protected:
	std::shared_ptr<Condition<E>> m_condition;
};

template <typename E>
NotCondition<E>::NotCondition() : m_condition()
{
}

template <typename E>
NotCondition<E>::NotCondition(std::shared_ptr<Condition<E>> condition) : m_condition(condition)
{
}

template <typename E>
NotCondition<E>::~NotCondition()
{
}

template <typename E>
void NotCondition<E>::setCondition(std::shared_ptr<Condition<E>> condition)
{
	//Try cast condition to complex condition, and ask if it's dependent on this
	std::shared_ptr<ComplexCondition<E>> complex = std::dynamic_pointer_cast<ComplexCondition<E>>(condition);
	if (complex.get() != nullptr && complex->isDependentOn(this)) {
		throw std::invalid_argument("Cannot set condition holding reference to this");
	}
	m_condition = condition;
}

template <typename E>
std::shared_ptr<Condition<E>> NotCondition<E>::getCondition()
{
	return m_condition;
}

template <typename E>
bool NotCondition<E>::isDependentOn(ComplexCondition<E>* condition)
{
	if (condition == this) {
		// Always dependent on self
		return true;
	}
	else if (condition == m_condition.get()) {
		// Dependent on m_condition
		return true;
	}
	else {
		// If m_condition is complex, this depends on anything m_condition depends upon
		std::shared_ptr<ComplexCondition<E>> complex = std::dynamic_pointer_cast<ComplexCondition<E>>(m_condition);
		if (complex.get() != nullptr) {
			return complex->isDependentOn(condition);
		}
		else {
			return false;
		}
	}
}

template <typename E>
bool NotCondition<E>::test(E entity)
{
	return !(m_condition->test(entity));
}
