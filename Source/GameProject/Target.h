#pragma once
#include "stdafx.h"
#include "Entity.h"
#include "Body.h"

class Target {
public:
	Target() {};
	virtual ~Target() {};

	virtual Target* clone() = 0;

	virtual glm::vec2 getPosition() = 0;

	virtual glm::vec2 getVelocity() = 0;
};

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

protected:
	glm::vec2 m_point;
};

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
		BodyPtr body = std::dynamic_pointer_cast<Body>(target->getComponent(Component::body));
		if (body) {
			return body->getVelocity();
		}
		else {
			return glm::vec2(0);
		}
	};

protected:
	EntityWeakPtr m_target;
};