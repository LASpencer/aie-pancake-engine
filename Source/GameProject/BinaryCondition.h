#pragma once
#include "ComplexCondition.h"

// Base class for complex conditions implementing binary boolean operations
template <typename E>
class BinaryCondition : public ComplexCondition<E> {
public:
	BinaryCondition();
	BinaryCondition(std::shared_ptr<Condition<E>> first, std::shared_ptr<Condition<E>> second);
	virtual ~BinaryCondition();

	void setFirstCondition(std::shared_ptr<Condition<E>> first);
	void setSecondCondition(std::shared_ptr<Condition<E>> second);

	std::shared_ptr<Condition<E>> getFirstCondition();
	std::shared_ptr<Condition<E>> getSecondCondition();

	virtual bool isDependentOn(ComplexCondition<E>* condition);
protected:
	std::shared_ptr<Condition<E>> m_first;
	std::shared_ptr<Condition<E>> m_second;
};

template <typename E>
BinaryCondition<E>::BinaryCondition() : m_first(), m_second()
{
}

template <typename E>
BinaryCondition<E>::BinaryCondition(std::shared_ptr<Condition<E>> first, std::shared_ptr<Condition<E>> second)
	: m_first(first), m_second(second)
{
}

template <typename E>
BinaryCondition<E>::~BinaryCondition()
{
}

template <typename E>
void BinaryCondition<E>::setFirstCondition(std::shared_ptr<Condition<E>> first)
{
	std::shared_ptr<ComplexCondition> complex = std::dynamic_pointer_cast<ComplexCondition>(first);
	if (complex.get() != nullptr && complex->isDependentOn(this)) {
		throw std::invalid_argument("Cannot set condition holding reference to this");
	}
	m_first = first;
}

template <typename E>
void BinaryCondition<E>::setSecondCondition(std::shared_ptr<Condition<E>> second)
{
	std::shared_ptr<ComplexCondition> complex = std::dynamic_pointer_cast<ComplexCondition>(second);
	if (complex.get() != nullptr && complex->isDependentOn(this)) {
		throw std::invalid_argument("Cannot set condition holding reference to this");
	}
	m_second = second;
}

template <typename E>
std::shared_ptr<Condition<E>> BinaryCondition<E>::getFirstCondition()
{
	return m_first;
}

template <typename E>
std::shared_ptr<Condition<E>> BinaryCondition<E>::getSecondCondition()
{
	return m_second;
}

template <typename E>
bool BinaryCondition<E>::isDependentOn(ComplexCondition<E> * condition)
{
	if (condition == this) {
		return true;
	}
	else if (condition == m_first.get() || condition == m_second.get()) {
		// Dependent on conditions
		return true;
	}
	else {
		// If complex first or second, this depends on anything they depend on
		std::shared_ptr<ComplexCondition> complexFirst = std::dynamic_pointer_cast<ComplexCondition>(m_first);
		std::shared_ptr<ComplexCondition> complexSecond = std::dynamic_pointer_cast<ComplexCondition>(m_second);
		bool firstDepends = false;
		bool secondDepends = false;
		if (complexFirst.get() != nullptr) {
			firstDepends = complexFirst->isDependentOn(condition);
		}
		if (complexSecond.get() != nullptr) {
			secondDepends = complexSecond->isDependentOn(condition);
		}
		return firstDepends || secondDepends;
	}
}
