#include "stdafx.h"
#include "Component.h"


Component::Component() : m_entity()
{
}


Component::~Component()
{
}

bool Component::onAdd(EntityPtr entity)
{
	// Check if already owned
	if (m_entity.expired()) {
		// Get weak reference to owning entity
		m_entity = EntityWeakPtr(entity);
		return true;
	}
	else {
		return false;
	}
}

void Component::onRemove(EntityPtr entity)
{
	// Checking entity is owner
	if (entity == m_entity.lock()) {
		m_entity.reset();
	}
}

EntityWeakPtr Component::getEntity()
{
	return m_entity;
}

