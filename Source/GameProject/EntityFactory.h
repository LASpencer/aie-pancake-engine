#pragma once
#include "stdafx.h"

class Entity;
typedef std::shared_ptr<Entity> EntityPtr;
typedef std::weak_ptr<Entity>	EntityWeakPtr;

class Component;
typedef std::shared_ptr<Entity> EntityPtr;
typedef std::weak_ptr<Entity>	EntityWeakPtr;

class SceneObject;
typedef std::shared_ptr<SceneObject> SceneObjectPtr;
typedef std::weak_ptr<SceneObject> SceneObjectWeakPtr;

struct Box;

class GameProjectApp;

/*	EntityFactory for creating different types of entity with the 
	appropriate components and tags. The entity is added to the
	app's list of entities.
*/
class EntityFactory {
public:

	// Different entities which can be created
	enum EntityType {
		hero,		// The player's character
		block,		// A square block
		platform,	// Long thin platform 
		floor,		// Long collider defining the floor
		door		// Door with a trigger collider
	};

	static const float hero_sprite_width;
	static const float hero_sprite_height;

	static const float block_sprite_width;
	static const float block_sprite_height;

	static const float platform_sprite_width;
	static const float platform_sprite_height;

	static const float door_sprite_width;
	static const float door_sprite_height;
	
	static const Box	block_hitbox;
	static const Box	platform_hitbox;
	static const Box	door_hitbox;
	static const Box	floor_hitbox;

	// Door position in background texture
	static const float door_uvx;
	static const float door_uvy;
	static const float door_uvw;
	static const float door_uvh;

	// Block position in background texture
	static const float block_uvx;
	static const float block_uvy;
	static const float block_uvw;
	static const float block_uvh;

	// Platform position in background texture
	static const float platform_uvx;
	static const float platform_uvy;
	static const float platform_uvw;
	static const float platform_uvh;


	EntityFactory(GameProjectApp* app);
	~EntityFactory();

	/** Creates an entity of specified type
	*	@param type Entity to create
	*	@param position Position to place entity at
	*	@return reference to created entity*/
	EntityPtr createEntity(EntityType type, glm::mat3 position = glm::mat3(1));
	
	/** Creates an entity of specified type
	*	@param type Entity to create
	*	@param position Position to place entity at
	*	@param parent SceneObject parent of position
	*	@return reference to created entity*/
	EntityPtr createEntity(EntityType type, glm::mat3 position, SceneObjectPtr parent);

	// Loads all resources used into the Resource Manager to prevent frame drops later
	void loadResources();

private:
	GameProjectApp* m_app;

	//// Creates a Hero entity
	//EntityPtr createHero(glm::mat3 position, SceneObjectPtr parent);
	//// Creates a Block entity
	//EntityPtr createBlock(glm::mat3 position, SceneObjectPtr parent);
	//// Creates a Platform entity
	//EntityPtr createPlatform(glm::mat3 position, SceneObjectPtr parent);
	//// Creates a Door entity
	//EntityPtr createDoor(glm::mat3 position, SceneObjectPtr parent);
	//// Creates a Floor entity
	//EntityPtr createFloor(glm::mat3 position, SceneObjectPtr parent);

	// Sets entity's position, and place in scene graph
	bool setEntityPosition(EntityPtr entity, glm::mat3 position, SceneObjectPtr parent);
};