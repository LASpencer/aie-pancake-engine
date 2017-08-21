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
	case(blue_base):
		entity = createBase(position, parent, true);
	break;
	case(red_base):
		entity = createBase(position, parent, false);
	break;
	case(depot):
		entity = createDepot(position, parent);
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
	m_app->getResourceManager()->getTexture(filepath::red_tank);
	m_app->getResourceManager()->getTexture(filepath::blue_tank);
	m_app->getResourceManager()->getTexture(filepath::red_base);
	m_app->getResourceManager()->getTexture(filepath::blue_base);
	m_app->getResourceManager()->getTexture(filepath::fuel_depot);
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
	Team team;
	setEntityPosition(tank, position, parent);
	tank->addTag(Entity::tank);
	if (isBlueTeam) {
		tank->addTag(Entity::blue_team);
		team = blue;
		sprite = m_app->getResourceManager()->getTexture(filepath::blue_tank);
	} else {
		tank->addTag(Entity::red_team);
		team = red;
		sprite = m_app->getResourceManager()->getTexture(filepath::red_tank);
	}
	// Add sprite
	tank->addComponent(std::make_shared<Sprite>(sprite, 60, 100));
	// Add collider
	ColliderPtr collider = std::make_shared<Collider>();
	//std::shared_ptr<AABox> box = std::make_shared<AABox>(glm::vec2(-18, -21), glm::vec2(18, 21), BoxType::body);
	//TODO set size based on sprite picked
	std::shared_ptr<OBox> box = std::make_shared<OBox>(glm::vec2(20, 0), glm::vec2(0, 26), glm::vec2(0, -5), BoxType::body);
	collider->addBox(std::static_pointer_cast<CollisionShape>(box));
	tank->addComponent(collider);
	// Add agent
	//TODO change to VehicleAgent when done
	//TODO create and add behaviour tree as suitable
	VehiclePtr agent = std::make_shared<VehicleAgent>(team, 100, 100, 100, 200, 31);
	tank->addComponent(agent);
	if (isBlueTeam) {
		m_app->getTeam(blue).push_back(agent);
	} else {
		m_app->getTeam(red).push_back(agent);
	}
	// Agent observes collider
	collider->addObserver(agent);

	return tank;
}

EntityPtr EntityFactory::createBase(glm::mat3 position, SceneObjectPtr parent, bool isBlueTeam)
{
	EntityPtr base = std::make_shared<Entity>(m_app);
	TexturePtr sprite;
	setEntityPosition(base, position, parent);
	base->addTag(Entity::base);
	if (isBlueTeam) {
		base->addTag(Entity::blue_team);
		sprite = m_app->getResourceManager()->getTexture(filepath::blue_base);
	}
	else {
		base->addTag(Entity::red_team);
		sprite = m_app->getResourceManager()->getTexture(filepath::red_base);
	}
	//Add sprite
	base->addComponent(std::make_shared<Sprite>(sprite));
	return base;
}

EntityPtr EntityFactory::createDepot(glm::mat3 position, SceneObjectPtr parent)
{
	EntityPtr depot = std::make_shared<Entity>(m_app);
	setEntityPosition(depot, position, parent);
	depot->addTag(Entity::depot);
	//Add sprite
	depot->addComponent(std::make_shared<Sprite>(m_app->getResourceManager()->getTexture(filepath::fuel_depot)));
	return depot;
}

bool EntityFactory::setEntityPosition(EntityPtr entity, glm::mat3 position, SceneObjectPtr parent)
{
	SceneObjectPtr pos = entity->getPosition();
	pos->setLocalTransform(position);
	// Add to scene graph
	return parent->addChild(pos);
}
