#pragma once
#include "Component.h"
#include "Behaviour.h"


class Agent 
	: public Component {
public:
	Agent();
	virtual ~Agent();

	// Returns Controller identifier
	virtual Identifier getID();

	// Tests whether entity is valid owner of this controller
	virtual bool isValidEntity(EntityPtr entity) = 0;

protected:
	std::vector<BehaviourPtr> m_behaviours;
};