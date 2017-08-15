#include "stdafx.h"
#include "VehicleAgent.h"

const float VehicleAgent::def_max_fuel = 100.f;
const float VehicleAgent::def_attack_range = 50.f;
const float VehicleAgent::idling_speed = 0.4f;
const float VehicleAgent::cruise_fuel_rate = 2.f;
const float VehicleAgent::idle_fuel_rate = 0.5f;
const float VehicleAgent::def_firing_rate = 1.f;

VehicleAgent::VehicleAgent() : Agent(), m_maxFuel(def_max_fuel), m_attackRange(def_attack_range), m_team(blue), m_alive(true), m_engineOK(true), m_canShoot(true), m_attackCD(0.f)
{
}

VehicleAgent::VehicleAgent(Team team, float attackRange, float maxFuel, float maxVelocity, float maxForce) : Agent(maxVelocity, maxForce), m_attackRange(attackRange), m_maxFuel(maxFuel), m_team(team), m_alive(true), m_engineOK(true), m_canShoot(true), m_attackCD(0.f)
{
}

VehicleAgent::~VehicleAgent()
{
}

void VehicleAgent::update(float deltaTime)
{
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
	
}

Team VehicleAgent::getTeam()
{
	return m_team;
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
	m_fuel += fuel;
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
		}
	}
	//TODO set uvrect of sprite for damage sustained, shooting
}
