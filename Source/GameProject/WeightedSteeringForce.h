#pragma once
#include "SteeringForce.h"

typedef std::pair<std::shared_ptr<SteeringForce>, float> ForceWeightPair;


class WeightedSteeringForce : public SteeringForce
{
public:
	WeightedSteeringForce();
	WeightedSteeringForce(const std::vector<ForceWeightPair>& list);
	//TODO copy, copy assign

	virtual ~WeightedSteeringForce();

	void setList(const std::vector<ForceWeightPair>& list);

	void addForce(ForceWeightPair force);

	void addForce(std::shared_ptr<SteeringForce> force, float weight);

	std::vector<ForceWeightPair>& getList();

	virtual glm::vec2 getForce(Agent* agent);

	virtual void draw(Agent* agent, aie::Renderer2D* renderer);

protected:
	std::vector<ForceWeightPair> m_weightedList;
};