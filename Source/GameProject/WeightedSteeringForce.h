#pragma once
#include "SteeringForce.h"

typedef std::pair<std::shared_ptr<SteeringForce>, float> WeightedForce;


class WeightedSteeringForce : public SteeringForce
{
public:
	WeightedSteeringForce();
	WeightedSteeringForce(const std::vector<WeightedForce>& list);
	//TODO copy, copy assign

	virtual ~WeightedSteeringForce();

	void setList(const std::vector<WeightedForce>& list);

	void addForce(WeightedForce force);

	void addForce(std::shared_ptr<SteeringForce> force, float weight);

	std::vector<WeightedForce>& getList();

	virtual glm::vec2 getForce(Agent* agent);

	virtual void draw(Agent* agent, aie::Renderer2D* renderer);

protected:
	std::vector<WeightedForce> m_weightedList;
};