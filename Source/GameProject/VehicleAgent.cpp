#include "stdafx.h"
#include "VehicleAgent.h"
#include "SpriteBase.h"
#include "Entity.h"
#include "GameProjectApp.h"

const float VehicleAgent::def_max_fuel = 100.f;
const float VehicleAgent::def_attack_range = 50.f;
const float VehicleAgent::neighbour_range = 300.f;
const float VehicleAgent::idling_speed = 0.4f;
const float VehicleAgent::cruise_fuel_rate = 2.f;
const float VehicleAgent::idle_fuel_rate = 0.5f;
const float VehicleAgent::def_firing_rate = 1.f;
const float VehicleAgent::tank_uvh = 1.f;
const float VehicleAgent::tank_uvw = 0.25f;
const float VehicleAgent::tank_default_uvx = 0.f;
const float VehicleAgent::tank_shooting_uvx = 0.25f;
const float VehicleAgent::tank_damaged_uvx = 0.5f;
const float VehicleAgent::tank_destroyed_uvx = 0.75f;

VehicleAgent::VehicleAgent() : Agent(), m_maxFuel(def_max_fuel), m_attackRange(def_attack_range), m_team(blue), m_alive(true), m_engineOK(true), m_canShoot(true), m_attackCD(0.f)
{
	m_fuel = m_maxFuel;
}

VehicleAgent::VehicleAgent(Team team, float attackRange, float maxFuel, float maxVelocity, float maxForce) : Agent(maxVelocity, maxForce), m_attackRange(attackRange), m_maxFuel(maxFuel), m_team(team), m_alive(true), m_engineOK(true), m_canShoot(true), m_attackCD(0.f)
{
	m_fuel = m_maxFuel;
}

VehicleAgent::~VehicleAgent()
{
}

void VehicleAgent::update(float deltaTime)
{
	// Get neighbours from app
	EntityPtr entity(m_entity);
	GameProjectApp* app = entity->getApp();
	for (VehiclePtr vehicle : app->getTeam(m_team)) {
		if (vehicle.get() != this) {
			glm::vec2 displacement = vehicle->getPosition() - getPosition();
			if (glm::dot(displacement, displacement) < neighbour_range * neighbour_range) {
				m_neighbours.push_back(vehicle.get());
			}
		}
	}
	float nearestEnemyDistance = INFINITY;
	for (VehiclePtr vehicle : app->getTeam((m_team == red) ? blue : red)) {
		glm::vec2 displacement = vehicle->getPosition() - getPosition();
		float distance = glm::dot(displacement, displacement);
		if (distance < neighbour_range * neighbour_range) {
			m_enemyNeighbours.push_back(vehicle.get());
		}
		// Set nearest enemy as target
		if (distance < nearestEnemyDistance) {
			nearestEnemyDistance = distance;
			m_target = std::dynamic_pointer_cast<AgentPtr>(vehicle);
		}
	}

	if (m_alive) {
		if (m_engineOK && m_canShoot) {
			setAnimationFrame(default);
		}
		else {
			setAnimationFrame(damaged);
		}
	}
	else {
		setAnimationFrame(destroyed);
	}
	Agent::update(deltaTime);
	if (m_attackCD > 0.f) {
		m_attackCD -= deltaTime;
	}

	if (m_engineOK) {
		if (glm::dot(m_velocity, m_velocity) > idling_speed * m_adjustedMaxVelocity) {
			m_fuel = std::max(0.f, m_fuel - deltaTime * cruise_fuel_rate);
		}
		else {
			m_fuel = std::max(0.f, m_fuel - deltaTime * idle_fuel_rate);
		}
	}
	if (m_fuel > 0 && m_engineOK) {
		m_canMove = true;
	} else {
		m_canMove = false;
	}

	// Clear neighbours
	m_neighbours.clear();
	m_enemyNeighbours.clear();
}

Team VehicleAgent::getTeam()
{
	return m_team;
}

std::vector<VehicleAgent*>& VehicleAgent::getNeighbours()
{
	return m_neighbours;
}

std::vector<VehicleAgent*>& VehicleAgent::getEnemyNeighbours()
{
	return m_enemyNeighbours;
}

float VehicleAgent::getMaxFuel()
{
	return m_maxFuel;
}

void VehicleAgent::setMaxFuel(float maxFuel)
{
	m_maxFuel = maxFuel;
}

float VehicleAgent::getFuel()
{
	return m_fuel;
}

void VehicleAgent::addFuel(float fuel)
{
	m_fuel = std::max(0.f, std::min(m_maxFuel, m_fuel + fuel));
}

bool VehicleAgent::isAlive()
{
	return false;
}

bool VehicleAgent::isEngineOK()
{
	return m_engineOK;
}

bool VehicleAgent::canShoot()
{
	return m_canShoot;
}

void VehicleAgent::attack(VehiclePtr target)
{
	if (m_canShoot && m_attackCD <= 0.f && m_team != target->getTeam()) {
		glm::vec2 displacement = target->getPosition() - getPosition();
		if (glm::dot(displacement, displacement) < m_attackRange * m_attackRange) {
			m_attackCD = def_firing_rate; //TODO replace with variable
			//TODO have attack/armour factor setting kill chances
			//TODO have chance of 
			float damageChance = 0.2f;
			//TODO split into catastrophicChance, mobilityChance, and firepowerChance

			float hitRoll = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			if (hitRoll >= 0.8f) {
				target->m_alive = false;
			}
			//Set attacking sprite
			// TODO maybe start countdown which, while on, shows attacking sprite?
			setAnimationFrame(shooting);
		}
	}
	//TODO set uvrect of sprite for damage sustained, shooting
}

void VehicleAgent::setAnimationFrame(TankAnimationFrame frame)
{
	float uvx = 0.f;
	switch (frame) {
	case(default):
		uvx = tank_default_uvx;
		break;
	case(shooting):
		uvx = tank_shooting_uvx;
		break;
	case(damaged):
		uvx = tank_damaged_uvx;
		break;
	case(destroyed):
		uvx = tank_destroyed_uvx;
		break;
	default:
		break;
	}
	EntityPtr entity(m_entity);
	SpriteBase* sprite = dynamic_cast<SpriteBase*>(entity->getComponent(Component::sprite).get());
	if (sprite != nullptr) {
		sprite->setUVRect(uvx, 0.f, tank_uvw, tank_uvh);
	}
}
