#pragma once
#include "Component.h"

class Body;

typedef std::shared_ptr<Body> BodyPtr;
typedef std::weak_ptr<Body>	BodyWeakPtr;

class Body 
	: public Component {
	Body();
	virtual ~Body();

	//TODO methods to alter
	//TODO update method

protected:
	//mass, velocity, force, drag, friction
};