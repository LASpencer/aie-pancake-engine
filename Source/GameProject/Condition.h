#pragma once
#include "stdafx.h"
#include "Entity.h"

template <typename E>
class Condition
{
public:
	Condition() {};
	virtual ~Condition() {};

	virtual bool test(std::shared_ptr<E> entity) = 0;
};