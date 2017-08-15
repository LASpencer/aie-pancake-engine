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
#include "VehicleAgent.h"
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
	case(red_tank):
		entity = createTank(position, parent, false);
		break;
	case(blue_tank):
		entity = createTank(position, parent, true);
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
	//std::shared_ptr<AABox> box = std::make_shared<AABox>(glm::vec2(-18, -21), glm::vec2(18, 21), BoxType::body);
	std::shared_ptr<OBox> box = std::make_shared<OBox>(glm::vec2(18, 0), glm::vec2(0, 21), glm::vec2(0,0), BoxType::body);
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

EntityPtr EntityFactory::createTank(glm::mat3 position, SceneObjectPtr parent, bool isBlueTeam)
{
	EntityPtr tank = std::make_shared<Entity>(m_app);
	TexturePtr sprite;
	setEntityPosition(tank, position, parent);
	tank->addTag(Entity::tank);
	if (isBlueTeam) {
		tank->addTag(Entity::blue_team);
		sprite = m_app->getResourceManager()->getTexture(filepath::blue_tank);
	} else {
		tank->addTag(Entity::red_team);
		sprite = m_app->getResourceManager()->getTexture(filepath::red_tank);
	}
	// Add sprite
	tank->addComponent(std::make_shared<Sprite>(sprite));
	// Add collider
	ColliderPtr collider = std::make_shared<Collider>();
	//std::shared_ptr<AABox> box = std::make_shared<AABox>(glm::vec2(-18, -21), glm::vec2(18, 21), BoxType::body);
	//TODO set size based on sprite picked
	std::shared_ptr<OBox> box = std::make_shared<OBox>(glm::vec2(18, 0), glm::vec2(0, 21), glm::vec2(0, 0), BoxType::body);
	collider->addBox(std::static_pointer_cast<CollisionShape>(box));
	tank->addComponent(collider);
	// Add agent
	//TODO change to VehicleAgent when done
	//TODO create and add behaviour tree as suitable
	VehiclePtr agent = std::make_shared<VehicleAgent>(100, 200);
	tank->addComponent(agent);
	if (isBlueTeam) {
		m_app->getBlueTeam().push_back(agent);
	} else {
		m_app->getRedTeam().push_back(agent);
	}
	// Agent observes collider
	collider->addObserver(agent);

	return tank;
}

bool EntityFactory::setEntityPosition(EntityPtr entity, glm::mat3 position, SceneObjectPtr parent)
{
	SceneObjectPtr pos = entity->getPosition();
	pos->setLocalTransform(position);
	// Add to scene graph
	return parent->addChild(pos);
}
