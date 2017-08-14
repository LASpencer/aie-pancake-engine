#pragma once
#include "EventBase.h"
#include "Collider.h"
#include "Grid.h"

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

	// True for collision id
	virtual bool isValidID(EventID id);	
};

class TerrainCollisionEvent
	:public EventBase {
public:
	/** Constructor
	*	@param square Grid square collided with
	*	@param myType type of hitbox owned by this
	*	@param penetration penetration of terrain into this*/
	TerrainCollisionEvent(GridSquareWeakPtr square, BoxType myType, glm::vec2 penetration);

	virtual ~TerrainCollisionEvent();

	GridSquareWeakPtr getSquare();

	BoxType getMyType();

	glm::vec2 getPenetration();

protected:
	GridSquareWeakPtr m_square;
	BoxType m_myType;
	glm::vec2 m_penetration;

	// True for terrain_collision id
	virtual bool isValidID(EventID id);
};