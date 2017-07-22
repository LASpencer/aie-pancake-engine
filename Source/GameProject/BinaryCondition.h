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