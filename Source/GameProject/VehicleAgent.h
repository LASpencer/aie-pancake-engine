#pragma once
#include "Agent.h"

class VehicleAgent : public Agent {
public:


protected:
	float m_fuel, m_maxFuel;
	bool m_alive, m_mobile, m_canShoot;
};