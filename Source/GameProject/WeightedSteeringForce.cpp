#include "stdafx.h"
#include "WeightedSteeringForce.h"
#include "utility.h"
#include "Agent.h"

WeightedSteeringForce::WeightedSteeringForce()
{
}

WeightedSteeringForce::WeightedSteeringForce(const std::vector<ForceWeightPair>& list)
{
	m_weightedList = list;
}

WeightedSteeringForce::~WeightedSteeringForce()
{
}

void WeightedSteeringForce::setList(const std::vector<ForceWeightPair>& list)
{
	m_weightedList = list;
}

void WeightedSteeringForce::addForce(ForceWeightPair force)
{
	m_weightedList.push_back(force);
}

void WeightedSteeringForce::addForce(std::shared_ptr<SteeringForce> force, float weight)
{
	m_weightedList.push_back(std::make_pair(force, weight));
}

std::vector<ForceWeightPair>& WeightedSteeringForce::getList()
{
	return m_weightedList;
}

glm::vec2 WeightedSteeringForce::getForce(Agent * agent)
{
	float maxForce = agent->getMaxForce();
	glm::vec2 totalForce(0);
	for (ForceWeightPair force : m_weightedList) {
		totalForce += force.first->getForce(agent) * force.second;
		if (glm::length(totalForce) > maxForce) {
			utility::clamp(totalForce, maxForce);
			break;
		}
	}
	return totalForce;
}

void WeightedSteeringForce::draw(Agent * agent, aie::Renderer2D * renderer)
{
	for (ForceWeightPair force : m_weightedList) {
		force.first->draw(agent, renderer);
	}
}
