#include "stdafx.h"
#include "Collider.h"
#include "Entity.h"
#include "CollisionEvent.h"
#include "CollisionShape.h"

bool Collider::draw_boxes = false;

Collider::Collider() : Component(), m_eventManager(this), m_localBoxes({}), m_globalBoxes({})
{
}


Collider::~Collider()
{
}

void Collider::setBoxes(std::vector<CollisionShapePtr> boxes)
{
	m_localBoxes = boxes;
}

void Collider::addBox(CollisionShapePtr box)
{
	m_localBoxes.push_back(box);
}

std::vector<CollisionShapePtr> Collider::getLocalBoxes()
{
	return m_localBoxes;
}

std::vector<CollisionShapePtr> Collider::getGlobalBoxes()
{
	return m_globalBoxes;
}

void Collider::addObserver(std::shared_ptr<Observer> observer)
{
	m_eventManager.addObserver(observer);
}

void Collider::removeObserver(std::shared_ptr<Observer> observer)
{
	m_eventManager.removeObserver(observer);
}

void Collider::clearObservers()
{
	m_eventManager.clearObservers();
}

void Collider::notifyObservers(EventBase * event)
{
	m_eventManager.notifyObservers(event);
}

bool Collider::isSubscribed(const Observer * observer) const
{
	return m_eventManager.isSubscribed(observer);
}

void Collider::update(float deltaTime)
{
	EntityPtr entity(m_entity);
	// Fill globalBoxes with copies of localBoxes
	m_globalBoxes.clear();
	for (CollisionShapePtr local : m_localBoxes) {
		CollisionShapePtr global(local->clone());
		// Transform each by entity's position
		global->transform(entity->getPosition()->getGlobalTransform());
		m_globalBoxes.push_back(global);
	}
}

void Collider::draw(aie::Renderer2D * renderer)
{
	if (draw_boxes) {
		//TODO: each shape has own draw method

		EntityPtr entity(m_entity);
		for (CollisionShapePtr box : m_globalBoxes) {
			// Set colour based on box type
			switch (box->getType()) {
			case(none):		//none is grey
				renderer->setRenderColour(0x80808080);
				break;
			case(body):		//body is blue
				renderer->setRenderColour(0x0000FF80);
				break;
			case(attack):	//attack is red
				renderer->setRenderColour(0xFF000080);
				break;
			case(trigger):	//trigger is green
				renderer->setRenderColour(0x00FF0080);
				break;
			default:
				break;
			}
			box->draw(renderer);
			renderer->setRenderColour(0xffffffff);
		}
	}
}

Collider::Identifier Collider::getID()
{
	return collider;
}

void Collider::resolveCollisions(std::vector<std::shared_ptr<Collider>> colliders, std::vector<std::shared_ptr<Collider>> neighbourColliders, std::vector<GridSquarePtr> terrain)
{
	std::vector<Collision> collisions{};		// Contains detected collisions
	std::vector<TerrainCollision> terrainCollisions;
	size_t numColliders = colliders.size();
	// Get collisions between each pair
	for (size_t i = 0; i < numColliders; ++i) {
		for (size_t j = i+1; j < numColliders; ++j) {
			//Test collision between boxes
			std::vector<Collision> currentCollisions = testCollision(colliders[i], colliders[j]);
			collisions.insert(collisions.end(), currentCollisions.begin(), currentCollisions.end());
		}
		// Test main colliders vs neighbours
		for (ColliderPtr neighbour : neighbourColliders) {
			std::vector<Collision> currentCollisions = testCollision(colliders[i], neighbour);
			collisions.insert(collisions.end(), currentCollisions.begin(), currentCollisions.end());
		}
		// Test main colliders vs terrain
		std::vector<TerrainCollision> currentCollisions = testCollision(colliders[i], terrain);
		terrainCollisions.insert(terrainCollisions.end(), currentCollisions.begin(), currentCollisions.end());
	}
	// For each collision, involved colliders notify observers
	for (Collision c : collisions) {
		CollisionEvent event1(c.collider[1]->getEntity(),c.type[0],c.type[1],c.penetration);
		CollisionEvent event2(c.collider[0]->getEntity(), c.type[1], c.type[0], -(c.penetration));
		c.collider[0]->notifyObservers(&event1);
		c.collider[1]->notifyObservers(&event2);
	}
	for (TerrainCollision c : terrainCollisions) {
		TerrainCollisionEvent event(c.square, c.type, c.penetration);
		c.collider->notifyObservers(&event);
	}
}



std::vector<Collision> Collider::testCollision(ColliderPtr a, ColliderPtr b)
{
	std::vector<Collision> collisions;
	for (CollisionShapePtr box1 : a->m_globalBoxes) {
		for (CollisionShapePtr box2 : b->m_globalBoxes) {
			std::pair<bool, glm::vec2> didCollide = box1->doesCollide(box2.get());
			if (didCollide.first) {
				collisions.push_back({ { a,b },{ box1->getType(),box2->getType() },didCollide.second });
			}
		}
	}
	return collisions;
}

std::vector<TerrainCollision> Collider::testCollision(ColliderPtr collider, std::vector<GridSquarePtr> squares)
{
	std::vector<TerrainCollision> collisions;
	for (CollisionShapePtr hitbox : collider->m_globalBoxes) {
		for (GridSquarePtr square : squares) {
			std::pair<bool, glm::vec2> didCollide = hitbox->doesCollide(square->getCollider().get());
			if (didCollide.first) {
				collisions.push_back({ collider, square, hitbox->getType(), didCollide.second });
			}
		}
	}
	return collisions;
}

void Collider::setDrawBoxes(bool shouldDraw)
{
	draw_boxes = shouldDraw;
}
