#include "stdafx.h"
#include "Entity.h"
#include "Component.h"

Entity::Entity() : m_position(std::make_shared<SceneObject>()), m_componentMask(0)
{
}


Entity::~Entity()
{
}

bool Entity::addComponent(const ComponentPtr & component)
{
	Component::Identifier id = component->getID();
	bool canAdd = true;
		if (m_componentMask & id) {
			// Can't add if already have component with same id
			canAdd = false;
		}
	if (canAdd) {
		// Try to add component to this
		canAdd = component->onAdd(shared_from_this());
		if (canAdd) {
			// If it worked, add component to container and mask
			m_components.push_back(component);
			m_componentMask |= id;
		}
	}
	return canAdd;
}

bool Entity::removeComponent(Component::Identifier id)
{
	std::vector<ComponentPtr>::iterator component = m_components.begin();
	bool removed = false;
	while (component != m_components.end()) {
		if ((*component)->getID() == id) {
			// If id matches, remove component from container and mask
			(*component)->onRemove(shared_from_this());
			component = m_components.erase(component);
			m_componentMask &= !id;
			removed = true;
			break;
		} else {
			++component;
		}
	}
	return removed;
}


int Entity::getComponentMask()
{
	return m_componentMask;
}

void Entity::addTag(ETag tag)
{
	m_tagMask |= tag;
}

void Entity::removeTag(ETag tag)
{
	m_tagMask &= !tag;
}

int Entity::getTagMask()
{
	return m_tagMask;
}

ComponentPtr Entity::getComponent(Component::Identifier id)
{
	for (ComponentPtr component : m_components) {
		if (component->getID() == id) {
			return component;
		}
	}
	// Return empty pointer if not found
	return ComponentPtr();
}

SceneObjectPtr Entity::getPosition()
{
	return m_position;
}

std::vector<EntityPtr> Entity::getEntitiesWithComponent(Component::Identifier component, std::vector<EntityPtr>&entities)
{
	// use find_if to fill new array with all entities with matching bitmask
	std::vector<EntityPtr> entitiesWithComponent;
	auto maskMatches = [=](EntityPtr e) {return bool(component&(e->getComponentMask())); };
	// Until end reached, push back next entity with matching component bitset
	std::vector<EntityPtr>::iterator entity = std::find_if(entities.begin(), entities.end(), maskMatches);
	while (entity != entities.end()) {
		entitiesWithComponent.push_back(*entity);
		entity = std::find_if(++entity, entities.end(), maskMatches);
	}
	return entitiesWithComponent;
}
