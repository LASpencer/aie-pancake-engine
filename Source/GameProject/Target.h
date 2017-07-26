#pragma once
#include "stdafx.h"
#include "Entity.h"
#include "Agent.h"

//TODO target can give its shape

class Target {
public:
	Target() {};
	virtual ~Target() {};

	virtual Target* clone() = 0;

	virtual glm::vec2 getPosition() = 0;

	virtual glm::vec2 getVelocity() = 0;

	virtual bool isValid() = 0;
};

typedef std::shared_ptr<Target> TargetPtr;
typedef std::weak_ptr<Target> TargetWeakPtr;

class PointTarget : public Target{
public:
	PointTarget() : m_point(0)
	{};

	PointTarget(glm::vec2 point) : m_point(point)
	{};

	virtual ~PointTarget() {};

	virtual Target* clone()
	{
		return new PointTarget(m_point);
	};

	void setTarget(glm::vec2 target)
	{
		m_point = target;
	};

	virtual glm::vec2 getPosition() 
	{
		return m_point; 
	};

	virtual glm::vec2 getVelocity() 
	{
		return glm::vec2(0);
	}

	virtual bool isValid()
	{
		return true;
	}

protected:
	glm::vec2 m_point;
};

typedef std::shared_ptr<PointTarget> PointTargetPtr;

class EntityTarget : public Target {
public:
	EntityTarget() : m_target()
	{};

	EntityTarget(EntityPtr target) : m_target(target)
	{};

	virtual ~EntityTarget() {};

	virtual Target* clone()
	{
		return new EntityTarget(m_target.lock());
	};

	void setTarget(EntityPtr target) {
		m_target = target;
	};

	virtual glm::vec2 getPosition()
	{
		EntityPtr target(m_target);
		return glm::vec2(target->getPosition()->getGlobalTransform()[2]);
	};

	virtual glm::vec2 getVelocity()
	{
		EntityPtr target(m_target);
		std::shared_ptr<Agent> agent = std::dynamic_pointer_cast<Agent>(target->getComponent(Component::agent));
		if (agent) {
			return agent->getVelocity();
		}
		else {
			return glm::vec2(0);
		}
	};

	virtual bool isValid() {
		return !m_target.expired();
	}

protected:
	EntityWeakPtr m_target;
};

typedef std::shared_ptr<EntityTarget> EntityTargetPtr;
