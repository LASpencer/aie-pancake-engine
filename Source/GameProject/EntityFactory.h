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
		ship,
		car
	};


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

	// Creates a Ship entity
	EntityPtr createShip(glm::mat3 position, SceneObjectPtr parent);

	EntityPtr createCar(glm::mat3 position, SceneObjectPtr parent);

	// Sets entity's position, and place in scene graph
	bool setEntityPosition(EntityPtr entity, glm::mat3 position, SceneObjectPtr parent);
};