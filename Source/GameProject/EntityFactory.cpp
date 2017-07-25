#include "stdafx.h"
#include "EntityFactory.h"
#include "GameProjectApp.h"
#include "Sprite.h"
#include "MultiSprite.h"
#include "Collider.h"
#include "Filepaths.h"
#include "SimpleAgent.h"
#include "KeyboardController.h"


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
	case(car):
		entity = createCar(position, parent);
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
	m_app->getResourceManager()->getTexture(filepath::ship);
	m_app->getResourceManager()->getTexture(filepath::car);
}


EntityPtr EntityFactory::createShip(glm::mat3 position, SceneObjectPtr parent)
{
	EntityPtr ship = std::make_shared<Entity>();
	setEntityPosition(ship, position, parent);
	// Add sprite
	ship->addComponent(std::make_shared<Sprite>(m_app->getResourceManager()->getTexture(filepath::ship)));
	// Add agent
	std::shared_ptr<SimpleAgent> agent = std::make_shared<SimpleAgent>();
	agent->addBehaviour(std::make_shared<KeyboardController>());
	ship->addComponent(agent);
	
	return ship;
}

EntityPtr EntityFactory::createCar(glm::mat3 position, SceneObjectPtr parent)
{
	EntityPtr car = std::make_shared<Entity>();
	setEntityPosition(car, position, parent);
	// Add sprite
	car->addComponent(std::make_shared<Sprite>(m_app->getResourceManager()->getTexture(filepath::car)));
	// Add agent
	car->addComponent(std::make_shared<SimpleAgent>(200, 1000));

	return car;
}

bool EntityFactory::setEntityPosition(EntityPtr entity, glm::mat3 position, SceneObjectPtr parent)
{
	SceneObjectPtr pos = entity->getPosition();
	pos->setLocalTransform(position);
	// Add to scene graph
	return parent->addChild(pos);
}
