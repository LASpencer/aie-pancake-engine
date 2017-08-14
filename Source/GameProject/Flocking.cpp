#include "stdafx.h"
#include "Flocking.h"
#include "GameProjectApp.h"

const float Flocking::def_separation_weight = 0.5f;
const float Flocking::def_alignment_weight = 1.f;
const float Flocking::def_cohesion_weight = 0.3f;
const float Flocking::def_range = 300.f;

Flocking::Flocking() : m_alignmentWeight(def_alignment_weight), m_cohesionWeight(def_cohesion_weight), m_separationWeight(def_separation_weight), m_range(def_range)
{
	m_alignment = std::make_shared<AlignmentForce>();
	m_cohesion = std::make_shared<CohesionForce>();
	m_separation = std::make_shared<SeparationForce>();
	isBoidRule = [](Agent* a) {return true; };
}

Flocking::Flocking(bool(*boidRule)(Agent *), float separationWeight, float alignmentWeight, float cohesionWeight, float range)
	: m_alignmentWeight(alignmentWeight), m_cohesionWeight(cohesionWeight), m_separationWeight(separationWeight), m_range(range), isBoidRule(boidRule)
{
	m_alignment = std::make_shared<AlignmentForce>();
	m_cohesion = std::make_shared<CohesionForce>();
	m_separation = std::make_shared<SeparationForce>();
}

Flocking::~Flocking()
{
}

Behaviour * Flocking::clone()
{
	return new Flocking(*this);
}

BehaviourResult Flocking::update(Agent * agent, float deltaTime)
{
	EntityPtr entity(agent->getEntity());
	std::vector<EntityPtr> entities = Entity::getEntitiesWithComponent(Component::agent, entity->getApp()->getEntityList());
	std::vector<AgentWeakPtr> neighbours;
	for (EntityPtr otherEntity : entities) {
		AgentPtr otherAgent = std::dynamic_pointer_cast<Agent>(otherEntity->getComponent(Component::agent));
		glm::vec2 displacement = otherAgent->getPosition() - agent->getPosition();
		if (otherAgent.get() != agent &&
			isBoidRule(otherAgent.get()) &&
			glm::dot(displacement, displacement) < m_range * m_range) {
			neighbours.push_back(AgentWeakPtr(otherAgent));
		}
	}
	if (neighbours.size() == 0) {
		return failure;
	}
	else {
		m_alignment->setNeighbours(neighbours);
		m_cohesion->setNeighbours(neighbours);
		m_separation->setNeighbours(neighbours);
		//TODO make these shared_ptrs instead
		agent->addForce(std::dynamic_pointer_cast<SteeringForce>(m_separation), m_separationWeight);
		agent->addForce(std::dynamic_pointer_cast<SteeringForce>(m_alignment), m_alignmentWeight);
		agent->addForce(std::dynamic_pointer_cast<SteeringForce>(m_cohesion), m_cohesionWeight);
	}
	return BehaviourResult();
}

void Flocking::setRule(bool(*newBoidRule)(Agent *))
{
	isBoidRule = newBoidRule;
}
