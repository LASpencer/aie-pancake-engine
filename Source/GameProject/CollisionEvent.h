#pragma once
#include "EventBase.h"
#include "Collider.h"

class Entity;
typedef std::weak_ptr<Entity> EntityWeakPtr;


class CollisionEvent
	: public EventBase {
public:
	/** Constructor
	*	@param other Entity this collided with
	*	@param myType type of hitbox owned by this
	*	@param otherType type of hitbox this collided with
	*	@param penetration penetration of other hitbox into this*/
	CollisionEvent(EntityWeakPtr other, BoxType myType, BoxType otherType, glm::vec2 penetration);


	virtual ~CollisionEvent();

	EntityWeakPtr getOtherEntity();

	BoxType getMyType();

	BoxType getOtherType();

	glm::vec2 getPenetration();

protected:
	EntityWeakPtr m_otherEntity;			// Entity collided with
	BoxType m_myType;						// Type of box owned by this
	BoxType m_otherType;					// Type of box collided with
	glm::vec2 m_penetration;				// Penetration of other box into this

	// True for collider id
	virtual bool isValidID(EventID id);	
};