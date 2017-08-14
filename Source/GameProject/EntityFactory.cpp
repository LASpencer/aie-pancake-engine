#include "stdafx.h"
#include "EntityFactory.h"
#include "GameProjectApp.h"
#include "Sprite.h"
#include "MultiSprite.h"
#include "Collider.h"
#include "AABox.h"
#include "OBox.h"
#include "CircleCollider.h"
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
	case(block):
		entity = createBlock(position, parent);
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
	EntityPtr ship = std::make_shared<Entity>(m_app);
	setEntityPosition(ship, position, parent);
	// Add sprite
	ship->addComponent(std::make_shared<Sprite>(m_app->getResourceManager()->getTexture(filepath::ship)));
	// Add agent
	std::shared_ptr<Agent> agent = std::make_shared<Agent>();
	agent->setBehaviour(std::make_shared<KeyboardController>());
	ship->addComponent(agent);
	
	return ship;
}

EntityPtr EntityFactory::createCar(glm::mat3 position, SceneObjectPtr parent)
{
	EntityPtr car = std::make_shared<Entity>(m_app);
	setEntityPosition(car, position, parent);
	car->addTag(Entity::car);
	// Add sprite
	car->addComponent(std::make_shared<Sprite>(m_app->getResourceManager()->getTexture(filepath::car)));
	// Add agent
	AgentPtr agent = std::make_shared<Agent>(100, 200);
	car->addComponent(agent);
	// Add collider
	ColliderPtr collider = std::make_shared<Collider>();
	std::shared_ptr<AABox> box = std::make_shared<AABox>(glm::vec2(-18, -21), glm::vec2(18, 21), BoxType::body);
	collider->addBox(std::static_pointer_cast<CollisionShape>(box));
	car->addComponent(collider);
	// Agent observes collider
	collider->addObserver(agent);
	return car;
}

EntityPtr EntityFactory::createBlock(glm::mat3 position, SceneObjectPtr parent)
{
	EntityPtr block = std::make_shared<Entity>(m_app);
	setEntityPosition(block, position, parent);
	block->addTag(Entity::immobile);
	// Add sprite
	block->addComponent(std::make_shared<Sprite>(m_app->getResourceManager()->getTexture(filepath::block)));
	// Add collider
	ColliderPtr collider = std::make_shared<Collider>();
	std::shared_ptr<AABox> box = std::make_shared<AABox>(glm::vec2(-38,-35), glm::vec2(38,35), BoxType::body);
	collider->addBox(std::static_pointer_cast<CollisionShape>(box));
	block->addComponent(collider);

	return block;
}

bool EntityFactory::setEntityPosition(EntityPtr entity, glm::mat3 position, SceneObjectPtr parent)
{
	SceneObjectPtr pos = entity->getPosition();
	pos->setLocalTransform(position);
	// Add to scene graph
	return parent->addChild(pos);
}
