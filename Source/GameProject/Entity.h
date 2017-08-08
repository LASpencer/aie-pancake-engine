#pragma once
#include "stdafx.h"
#include "Renderer2D.h"
#include "Component.h"
#include "SceneObject.h"

class GameProjectApp;

class Entity;
typedef std::shared_ptr<Component> ComponentPtr;
typedef std::shared_ptr<Entity> EntityPtr;
typedef std::weak_ptr<Entity>	EntityWeakPtr;

/* Entity class.
	An Entity is a collection of Components and a position. Each 
	component uses the entity's position, and may interact with other
	components used by it. 
	The entity may also have several tags providing further information
	about it, to allow other objects to treat it appropriately.

	Entities hold shared_ptrs to their components and SceneObject,
	and a shared_ptr to each entity is held by the GameProjectApp
*/
class Entity : public std::enable_shared_from_this<Entity>
{
public:

	//	Tags which can be added to an entity
	enum ETag {
		player = 0x1,	// Entity is the player
		floor = 0x2,	// Entity can be walked on and support entities
		door = 0x4		// Entity is a door
	};

	Entity(GameProjectApp* app);
	virtual ~Entity();

	/** Adds a component to the entity
	*	@param component Component to be added
	*	@return true if component was successfully added*/
	bool addComponent(const ComponentPtr& component);

	/**	Removes a component from the entity
	*	@param id Identifier for component to remove
	*	@return true if component removed, false if not found in entity*/
	bool removeComponent(Component::Identifier id);

	int getComponentMask();

	void addTag(ETag tag);

	void removeTag(ETag tag);

	int getTagMask();

	/** Gets component matching identifier
	*	@param id Identifier for component wanted
	*	@return component with matching id, or empty ComponentPtr if not found*/
	ComponentPtr getComponent(Component::Identifier id);

	SceneObjectPtr getPosition();

	GameProjectApp* getApp();

	/** Returns array of entities with a particular type of component
	*	@param component Identifier for component class to search for
	*	@param entities Array containing entities to check
	*	@return Array of references to entities with that component
	*/
	static std::vector<EntityPtr> getEntitiesWithComponent(Component::Identifier component, std::vector<EntityPtr>& entities);

protected:
	std::vector<ComponentPtr> m_components;
	int m_componentMask;
	int m_tagMask;
	SceneObjectPtr m_position;
	GameProjectApp* m_app;
};

