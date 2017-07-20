#pragma once
#include "Component.h"

/*	Abstract base class for components which control and manage the entity
	This should be the last component added, as it may depend on other components*/
class Controller 
	: public Component {
public:
	Controller();
	virtual ~Controller();

	// Returns Controller identifier
	virtual Identifier getID();

	// Tests whether entity is valid owner of this controller
	virtual bool isValidEntity(EntityPtr entity) = 0;
};