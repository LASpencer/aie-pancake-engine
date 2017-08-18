#pragma once
#include "Behaviour.h"
#include "SeparationForce.h"

class FleeDanger : public Behaviour {
public:
	FleeDanger();

	virtual ~FleeDanger();

	virtual Behaviour* clone();

	virtual BehaviourResult update(Agent* agent, float deltaTime);

protected:
	std::shared_ptr<SeparationForce> m_separation;
};