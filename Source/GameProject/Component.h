#pragma once
#include "stdafx.h"
#include "Renderer2D.h"

class Entity;
typedef std::shared_ptr<Entity> EntityPtr;
typedef std::weak_ptr<Entity>	EntityWeakPtr;

/* Abstract class for components which can be attached to entities
	Provides interface for updating and drawing component, as well as
	getting an Identifier value to check the derived class and determine
	an entity's component bitmask

	A Component is held as a shared_ptr by its owning Entity, and holds a
	weak reference to that entity.
*/
class Component
{
public:
	Component();
	virtual ~Component();

	virtual void update(float deltaTime) = 0;

	virtual void draw(aie::Renderer2D* renderer) {};

	/** Sets entity as owner, unless already owned
	*	@param entity Entity trying to add this component
	*	@return true if can be added, false if already owned*/
	virtual bool onAdd(EntityPtr entity);

	/** Removes reference to owner
	*	@param entity removing this component */
	virtual void onRemove(EntityPtr entity);

	/* Values for different Component derived classes, so an
		Entity won't add redundant components, and components
		with the same tasks can be updated together
	
		These are used to generate a bitmask, so no two values
		share the same on bits.
	
	*	sprite (1):		SpriteBase		Draws entity
	
	*	collider (2):	Collider		Contains entity's hitboxes
										and tests for collisions
	
	*	agent (4):		Agent			Controls entity's behaviour

	*	body (8):		Body			Moves entity //TODO update comments
	*/
	enum Identifier {
		sprite = 0x1,		// Derived from SpriteBase class
		collider = 0x2,		// Collider class
		agent = 0x4,	// Derived from Controller class
		body = 0x8
	};

	// Returns identifier for derived class type
	virtual Identifier getID() = 0;

	// Returns entity owning this component
	EntityWeakPtr getEntity();

protected:
	EntityWeakPtr m_entity;
};

// Exception indicating an entity does not have a component it was expected to have
class missing_component : public std::logic_error {
public:
	explicit missing_component(const std::string& what_arg) : std::logic_error(what_arg)
	{};
	explicit missing_component(const char* what_arg) : std::logic_error(what_arg)
	{};

	virtual ~missing_component() {};
};