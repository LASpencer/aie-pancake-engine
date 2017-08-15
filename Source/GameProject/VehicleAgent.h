#pragma once
#include "Agent.h"

class VehicleAgent;
typedef std::shared_ptr<VehicleAgent> VehiclePtr;

enum Team {
	red,
	blue
};

class VehicleAgent : public Agent {
public:
	static const float def_max_fuel;
	static const float def_attack_range;
	static const float idling_speed;
	static const float cruise_fuel_rate;
	static const float idle_fuel_rate;
	static const float def_firing_rate;
	
	VehicleAgent();
	VehicleAgent(Team team, float attackRange = def_attack_range, float maxFuel = def_max_fuel, float maxVelocity = def_max_velocity, float maxForce = def_max_force);

	virtual ~VehicleAgent();

	virtual void update(float deltaTime);

	Team getTeam();

	float getMaxFuel();

	void setMaxFuel(float maxFuel);

	float getFuel();

	void addFuel(float fuel);

	bool isAlive();

	bool isEngineOK();

	bool canShoot();

	// If target is in range, and 
	void attack(VehiclePtr target);

protected:
	float m_fuel, m_maxFuel, m_attackRange, m_attackCD;
	bool m_alive, m_engineOK, m_canShoot;
	Team m_team;
};