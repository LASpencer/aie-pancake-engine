#include "stdafx.h"
#include "EntityFactory.h"
#include "GameProjectApp.h"
#include "Sprite.h"
#include "MultiSprite.h"
#include "Collider.h"
#include "Filepaths.h"
#include "Body.h"
#include "ShipAgent.h"


EntityFactory::EntityFactory(GameProjectApp* app) : m_app(app)
{
}

EntityFactory::~EntityFactory()
{
}

EntityPtr EntityFactory::createEntity(EntityType type, glm::mat3 position)
{
	// Default parent is root node from app
	return createEntity(type, position, m_app->getSceneRoot());
}

EntityPtr EntityFactory::createEntity(EntityType type, glm::mat3 position, SceneObjectPtr parent)
{
	EntityPtr entity;
	// Select method for creating entity
	switch (type) {
	case(ship):
		entity = createShip(position, parent);
		break;
	default:
		break;
	}
	// Add entity to app's list
	m_app->getEntityList().push_back(entity);
	return entity;
}

void EntityFactory::loadResources()
{
	//TODO load sprites needed for entities
}


EntityPtr EntityFactory::createShip(glm::mat3 position, SceneObjectPtr parent)
{
	EntityPtr ship = std::make_shared<Entity>();
	setEntityPosition(ship, position, parent);
	//TODO add tags
	// Add sprite
	ship->addComponent(std::make_shared<Sprite>(m_app->getResourceManager()->getTexture(filepath::ship)));
	// Add body
	ship->addComponent(std::make_shared<Body>(1, 4.f));
	// TODO collider?
	// Add agent
	ship->addComponent(std::make_shared<ShipAgent>());
	
	return ship;
}

bool EntityFactory::setEntityPosition(EntityPtr entity, glm::mat3 position, SceneObjectPtr parent)
{
	SceneObjectPtr pos = entity->getPosition();
	pos->setLocalTransform(position);
	// Add to scene graph
	return parent->addChild(pos);
}
