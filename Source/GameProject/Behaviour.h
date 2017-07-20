#pragma once
#include "stdafx.h"

class Entity;
typedef std::shared_ptr<Entity> EntityPtr;

class Behaviour;
typedef std::shared_ptr<Behaviour> BehaviourPtr;

class Behaviour
{
public:
	virtual void update(EntityPtr entity, float deltaTime) = 0;
};
