#pragma once
#include "stdafx.h"
#include "SteeringForce.h"

class KeyboardControlForce : public SteeringForce
{
public:
	KeyboardControlForce();

	virtual ~KeyboardControlForce();

	virtual glm::vec2 getForce(Agent* agent);
};