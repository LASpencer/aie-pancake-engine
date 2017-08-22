#pragma once
#include "Agent.h"


class VehicleAgent;
typedef std::shared_ptr<VehicleAgent> VehiclePtr;

enum Team {
	red,
	blue
};

enum TankAnimationFrame {
	default,
	shooting,
	damaged,
	destroyed
};

class VehicleAgent : public Agent {
public:
	static const float def_max_fuel;
	static const float def_attack_range;
	static const float neighbour_range;
	static const float idling_speed;
	static const float cruise_fuel_rate;
	static const float idle_fuel_rate;
	static const float def_firing_rate;
	static const float shoot_time;

	static const float tank_uvh;
	static const float tank_uvw;
	static const float tank_default_uvx;
	static const float tank_shooting_uvx;
	static const float tank_damaged_uvx;
	static const float tank_destroyed_uvx;
	
	VehicleAgent();
	VehicleAgent(Team team, float attackRange = def_attack_range, float maxFuel = def_max_fuel, float maxVelocity = def_max_velocity, float maxForce = def_max_force, float size = def_size);

	virtual ~VehicleAgent();

	virtual void update(float deltaTime);

	Team getTeam();

	std::vector<VehicleAgent*>& getNeighbours();

	std::vector<VehicleAgent*>& getEnemyNeighbours();

	float getMaxFuel();

	void setMaxFuel(float maxFuel);

	float getFuel();

	void addFuel(float fuel);

	bool isAlive();

	bool isEngineOK();

	bool canShoot();


	// If target is in range, and 
	bool attack(VehiclePtr target);

	void kill();

	void respawn();

	void setAnimationFrame(TankAnimationFrame frame);

protected:
	float m_fuel, m_maxFuel, m_attackRange, m_attackCD, m_shootTime;
	bool m_alive, m_engineOK, m_canShoot;
	Team m_team;
	PursueForcePtr m_pursueForce;
	std::vector<VehicleAgent*> m_neighbours;
	std::vector<VehicleAgent*> m_enemyNeighbours;
};