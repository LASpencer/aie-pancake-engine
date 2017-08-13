#pragma once
#include "SteeringForce.h"
#include "Ray.h"

class AvoidTerrainForce;
typedef std::shared_ptr<AvoidTerrainForce> AvoidTerrainForcePtr;

class AvoidTerrainForce : public SteeringForce {
public:
	AvoidTerrainForce();

	virtual ~AvoidTerrainForce();

	virtual glm::vec2 getForce(Agent* agent);

	virtual void draw(Agent* agent, aie::Renderer2D* renderer);
};