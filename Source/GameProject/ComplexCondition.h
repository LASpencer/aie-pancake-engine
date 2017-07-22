#pragma once
#include "Condition.h"

/** Abstract class for conditions which use other conditions
*	Provides a common interface to more easily allow tree traversal
*/
template <typename E>
class ComplexCondition : public Condition<E> {
public:
	ComplexCondition() {};
	virtual ~ComplexCondition() {};

	// Returns true if condition's test will be called by the complex condition's test
	virtual bool isDependentOn(ComplexCondition<E>* condition) = 0;
};