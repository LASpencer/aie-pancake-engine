#pragma once
#include "Component.h"
#include "Subject.h"
#include "EventManager.h"


class CollisionShape;
typedef std::shared_ptr<CollisionShape> CollisionShapePtr;

class GridSquare;

typedef std::shared_ptr<GridSquare> GridSquarePtr;
typedef std::weak_ptr<GridSquare> GridSquareWeakPtr;

class Ray;

/* Enumeration of different types of hitboxes
	Used to determine collision resolution*/
enum BoxType {
	none,
	body,		// Used for physical collisions
	attack,		// Used for attack hitboxes
	trigger,	// Triggers some event when collided with
	terrain		// Used for grid squares
};

// A hitbox used for collision testing and resolution
struct Box {
	glm::vec2 corner1;
	glm::vec2 corner2;
	BoxType type;

};

//TODO rewrite to take arbitrary colliders
class Collider;

typedef std::shared_ptr<Collider> ColliderPtr;
typedef std::weak_ptr<Collider>	ColliderWeakPtr;

// Contains data representing a collision between two hitboxes
struct Collision {
	std::shared_ptr<Collider>	collider[2];	// Colliders containing the boxes
	BoxType		type[2];						// Types of first and second box
	glm::vec2	penetration;		// Penetration of second box into first
};

// Contains data representing a collision between a collider and terrain
struct TerrainCollision {
	ColliderPtr		collider;
	GridSquarePtr	square;
	BoxType			type;
	glm::vec2		penetration;
};

/*	Component containing hitboxes, allowing entity to collide with other entities
	Collider is also a Subject, producing CollisionEvents when a collision occurs
	informing the Observers to respond appropriately.
*/
class Collider :
	public Component, public Subject
{
public:
	static bool draw_boxes;		//If true, display hitboxes coloured according to BoxType

	Collider();
	virtual ~Collider();

	void setBoxes(std::vector<CollisionShapePtr> boxes);

	void addBox(CollisionShapePtr box);

	std::vector<CollisionShapePtr> getLocalBoxes();
	std::vector<CollisionShapePtr> getGlobalBoxes();


	virtual void addObserver(std::shared_ptr<Observer> observer);
	virtual void removeObserver(std::shared_ptr<Observer> observer);
	virtual void clearObservers();
	virtual void notifyObservers(EventBase* event);
	virtual bool isSubscribed(const Observer* observer) const;

	// Updates global position of hitboxes
	virtual void update(float deltaTime);

	/** If draw_boxes set to true, draw hitboxes
	*	@param renderer Renderer2D to draw boxes to*/
	virtual void draw(aie::Renderer2D* renderer);

	// Returns Collider identifier
	virtual Identifier getID();

	/**	Tests for collisions and has colliders involved produce collision events
	*	@param colliders Colliders being checked for collision*/
	static void resolveCollisions(std::vector <std::shared_ptr<Collider>>& colliders, std::vector<GridSquarePtr>& terrain);

	// Tests for collisions between two colliders
	static std::vector<Collision> testCollision(ColliderPtr a, ColliderPtr b);

	// Tests collision between collider and terrain
	static std::vector<TerrainCollision> testCollision(ColliderPtr collider, std::vector<GridSquarePtr>& squares);

	static void setDrawBoxes(bool shouldDraw);

protected:
	EventManager m_eventManager;
	
	std::vector<CollisionShapePtr> m_localBoxes;	// Hitboxes with position relative to entity's position
	std::vector<CollisionShapePtr> m_globalBoxes;	// Hitboxes with global positon
};

