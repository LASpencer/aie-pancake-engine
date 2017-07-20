#include "stdafx.h"
#include "EntityFactory.h"
#include "GameProjectApp.h"
#include "Sprite.h"
#include "MultiSprite.h"
#include "Collider.h"
#include "Filepaths.h"



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
	///*switch (type) {
	//case(hero):
	//	entity = createHero(position, parent);
	//	break;
	//case(block):
	//	entity = createBlock(position, parent);
	//	break;
	//case(platform):
	//	entity = createPlatform(position, parent);
	//	break;
	//case(door):
	//	entity = createDoor(position, parent);
	//	break;
	//case(floor):
	//	entity = createFloor(position, parent);
	//	break;
	//default:
	//	break;
	//}*/
	// Add entity to app's list
	m_app->getEntityList().push_back(entity);
	return entity;
}

void EntityFactory::loadResources()
{
	//TODO load sprites needed for entities
}

//EntityPtr EntityFactory::createHero(glm::mat3 position, SceneObjectPtr parent)
//{
//	EntityPtr hero = std::make_shared<Entity>();
//	setEntityPosition(hero, position, parent);
//	// Tag as player
//	hero->addTag(Entity::player);
//	// Start with idle pose uvRect
//	std::pair<float, float> startFrame = HeroController::animation_frames.at(HeroController::idle);
//	// Add MultiSprite with hero textures
//	las::Array<TexturePtr> textures({
//		m_app->getResourceManager()->getTexture(filepath::hero_sprite),
//		m_app->getResourceManager()->getTexture(filepath::hero_robe),
//		m_app->getResourceManager()->getTexture(filepath::hero_armour),
//		m_app->getResourceManager()->getTexture(filepath::hero_helmet),
//		m_app->getResourceManager()->getTexture(filepath::hero_shield) });
//	hero->addComponent(std::make_shared<MultiSprite>(textures,
//		hero_sprite_width, hero_sprite_height, startFrame.first, startFrame.second,
//		HeroController::sprite_uv_width, HeroController::sprite_uv_height));
//	// Add empty collider, as controller will set hitboxes
//	hero->addComponent(std::make_shared<Collider>());
//	// Add HeroController last, as it depends on other components
//	hero->addComponent(std::make_shared<HeroController>());
//	//TODO add a sword entity, child of the hero, to entity list after hero
//	// hero has weakptr to it
//	return hero;
//}
//
//EntityPtr EntityFactory::createBlock(glm::mat3 position, SceneObjectPtr parent)
//{
//	EntityPtr block = std::make_shared<Entity>();
//	setEntityPosition(block, position, parent);
//	// Tag as floor, so it can be walked on
//	block->addTag(Entity::floor);
//	// Add sprite
//	block->addComponent(std::make_shared<Sprite>(m_app->getResourceManager()->getTexture(filepath::castle_tiles),
//		block_sprite_width, block_sprite_height, block_uvx, block_uvy, block_uvw, block_uvh));
//	// Add collider with body hitbox
//	std::shared_ptr<Collider> collider = std::make_shared<Collider>();
//	collider->setBoxes({ block_hitbox });
//	block->addComponent(collider);
//	return block;
//}
//
//EntityPtr EntityFactory::createPlatform(glm::mat3 position, SceneObjectPtr parent)
//{
//	EntityPtr platform = std::make_shared<Entity>();
//	setEntityPosition(platform, position, parent);
//	// Tag as floor, so it can be walked on
//	platform->addTag(Entity::floor);
//	// Add sprite
//	platform->addComponent(std::make_shared<Sprite>(m_app->getResourceManager()->getTexture(filepath::castle_tiles),
//		platform_sprite_width, platform_sprite_height, platform_uvx, platform_uvy, platform_uvw, platform_uvh));
//	// Add collider with body hitbox
//	std::shared_ptr<Collider> collider = std::make_shared<Collider>();
//	collider->setBoxes({ platform_hitbox });
//	platform->addComponent(collider);
//	return platform;
//
//}
//
//EntityPtr EntityFactory::createDoor(glm::mat3 position, SceneObjectPtr parent)
//{
//	EntityPtr door = std::make_shared<Entity>();
//	setEntityPosition(door, position, parent);
//	// Tag as door
//	door->addTag(Entity::door);
//	// Add sprite 
//	door->addComponent(std::make_shared<Sprite>(m_app->getResourceManager()->getTexture(filepath::castle_tiles),
//		door_sprite_width, door_sprite_height, door_uvx, door_uvy, door_uvw, door_uvh));
//	// Add collider with trigger hitbox
//	std::shared_ptr<Collider> collider = std::make_shared<Collider>();
//	collider->setBoxes({ door_hitbox });
//	door->addComponent(collider);
//	return door;
//}
//
//EntityPtr EntityFactory::createFloor(glm::mat3 position, SceneObjectPtr parent)
//{
//	EntityPtr floor = std::make_shared<Entity>();
//	setEntityPosition(floor, position, parent);
//	// Tag as floor
//	floor->addTag(Entity::floor);
//	// Add collider with long body hitbox
//	std::shared_ptr<Collider> collider = std::make_shared<Collider>();
//	collider->setBoxes({ floor_hitbox });
//	floor->addComponent(collider);
//	return floor;
//}

bool EntityFactory::setEntityPosition(EntityPtr entity, glm::mat3 position, SceneObjectPtr parent)
{
	SceneObjectPtr pos = entity->getPosition();
	pos->setLocalTransform(position);
	// Add to scene graph
	return parent->addChild(pos);
}
