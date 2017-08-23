#pragma once
#include "stdafx.h"
#include "SteeringForce.h"

class SeekForce;
typedef std::shared_ptr<SeekForce> SeekForcePtr;

// Move to goal position, without slowing down
class SeekForce :
	public SteeringForce
{
public:
	SeekForce();

	SeekForce(glm::vec2 goal); 

	SeekForce(const SeekForce& other);

	SeekForce& operator=(const SeekForce& other);

	virtual ~SeekForce();

	void setGoal(glm::vec2 goal);

	virtual glm::vec2 getForce(Agent* agent);

protected:
	glm::vec2 m_goal;
};