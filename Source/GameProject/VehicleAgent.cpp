#include "stdafx.h"
#include "VehicleAgent.h"
#include "SpriteBase.h"
#include "Entity.h"
#include "GameProjectApp.h"
#include "SeparationForce.h"
#include "AlignmentForce.h"
#include "CohesionForce.h"

const float VehicleAgent::def_max_fuel = 100.f;
const float VehicleAgent::def_attack_range = 100.f;
const float VehicleAgent::neighbour_range = 300.f;
const float VehicleAgent::idling_speed = 0.4f;
const float VehicleAgent::cruise_fuel_rate = 2.f;
const float VehicleAgent::idle_fuel_rate = 0.5f;
const float VehicleAgent::def_firing_rate = 1.f;
const float VehicleAgent::shoot_time = 0.2f;
const float VehicleAgent::def_alignment_weight = 0.3f;
const float VehicleAgent::def_cohesion_weight = 0.2f;
const float VehicleAgent::def_separation_weight = 0.2f;
const float VehicleAgent::tank_uvh = 1.f;
const float VehicleAgent::tank_uvw = 0.25f;
const float VehicleAgent::tank_default_uvx = 0.f;
const float VehicleAgent::tank_shooting_uvx = 0.25f;
const float VehicleAgent::tank_damaged_uvx = 0.5f;
const float VehicleAgent::tank_destroyed_uvx = 0.75f;

VehicleAgent::VehicleAgent() : Agent(), m_maxFuel(def_max_fuel), m_attackRange(def_attack_range), m_team(blue), m_alive(true), m_engineOK(true), m_canShoot(true), m_attackCD(0.f), m_shootTime(0.f)
{
	m_fuel = m_maxFuel;
	m_separation = std::make_shared<SeparationForce>();
	m_cohesion = std::make_shared<CohesionForce>();
	m_alignment = std::make_shared<AlignmentForce>();
}

VehicleAgent::VehicleAgent(Team team, float attackRange, float maxFuel, float maxVelocity, float maxForce, float size) : Agent(maxVelocity, maxForce, size), m_attackRange(attackRange), m_maxFuel(maxFuel), m_team(team), m_alive(true), m_engineOK(true), m_canShoot(true), m_attackCD(0.f), m_shootTime(0.f)
{
	m_fuel = m_maxFuel;
	m_separation = std::make_shared<SeparationForce>();
	m_cohesion = std::make_shared<CohesionForce>();
	m_alignment = std::make_shared<AlignmentForce>();
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
	bool targetAlive = false;
	for (VehiclePtr vehicle : app->getTeam((m_team == red) ? blue : red)) {
		glm::vec2 displacement = vehicle->getPosition() - getPosition();
		float distance = glm::dot(displacement, displacement);
		if (distance < neighbour_range * neighbour_range) {
			m_enemyNeighbours.push_back(vehicle.get());
		}
		// Set nearest live enemy if possible, or nearest dead if no live found
		if (distance < nearestEnemyDistance || (!targetAlive && vehicle->isAlive())) {
			nearestEnemyDistance = distance;
			targetAlive = vehicle->isAlive();
			m_target = std::dynamic_pointer_cast<Agent>(vehicle);
		}
	}

	if (m_alive) {
		if (m_engineOK) {
			if (m_shootTime > 0.f) {
				setAnimationFrame(shooting);
			}
			else {
				setAnimationFrame(default);
			}
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
	if (m_shootTime > 0.f) {
		m_shootTime -= deltaTime;
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
		m_timers[immobile].reset();
		m_timers[immobile].pause();
	} else {
		m_canMove = false;
		m_timers[immobile].start();
		// Kill if immobile too long
		if (m_timers[immobile].getTime() > 5.f) {
			kill();
		}
	}
	if (m_alive) {
		m_timers[dead].reset();
		m_timers[dead].pause();
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
	return m_alive;
}

bool VehicleAgent::isEngineOK()
{
	return m_engineOK;
}

bool VehicleAgent::canShoot()
{
	return m_canShoot;
}


bool VehicleAgent::attack(VehiclePtr target)
{
	if (m_canShoot && target->isAlive() && m_team != target->getTeam()) {
		glm::vec2 displacement = target->getPosition() - getPosition();
		if (glm::dot(displacement, displacement) < m_attackRange * m_attackRange) {
			if (m_attackCD <= 0.f) {
				// Sets shooting cooldown
				m_attackCD = def_firing_rate;
				// Check if attack hits
				float damageChance = 0.2f;
				float hitRoll = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				if (hitRoll >= 0.8f) {
					target->kill();
				}
				// Setting shootTime turns on shooting sprite
				m_shootTime = shoot_time;
			}
			return true;
		}
	}
	return false;
}

void VehicleAgent::kill()
{
	if (m_alive) {
		m_alive = false;
		m_engineOK = false;
		m_canShoot = false;
		m_timers[dead].start();		// Starting dead timer so it knows when to respawn
	}
}

void VehicleAgent::respawn()
{
	m_alive = true;
	m_engineOK = true;
	m_canShoot = true;
	m_fuel = m_maxFuel;
	// Move back to base
	EntityPtr entity(m_entity);
	EntityPtr base = entity->getApp()->getBase(m_team);
	glm::vec2 basePos(base->getPosition()->getGlobalTransform()[2]);
	entity->getPosition()->globalTranslate(basePos - getPosition());
}

void VehicleAgent::flock(float separationWeight, float alignmentWeight, float cohesionWeight)
{
	m_steeringForces.push_back({ std::dynamic_pointer_cast<SteeringForce>(m_separation), separationWeight });
	m_steeringForces.push_back({ std::dynamic_pointer_cast<SteeringForce>(m_alignment), alignmentWeight });
	m_steeringForces.push_back({ std::dynamic_pointer_cast<SteeringForce>(m_cohesion), cohesionWeight });
}

void VehicleAgent::avoidFriends(float separationWeight)
{
	m_steeringForces.push_back({ std::dynamic_pointer_cast<SteeringForce>(m_separation), separationWeight });
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
