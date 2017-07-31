#include "stdafx.h"
#include "SceneObject.h"


SceneObject::SceneObject() : m_parent(), m_children(), m_localTransform(1),m_globalTransform(1),dirtyGlobal(true)
{
}

SceneObject::SceneObject(glm::mat3 localTransform, SceneObjectPtr parent)
{
}

SceneObject::SceneObject(const SceneObject & other) : m_parent(), m_children(), m_localTransform(other.m_localTransform), m_globalTransform(1),dirtyGlobal(true)
{
	other.m_parent->addChild(shared_from_this());
}

SceneObject & SceneObject::operator=(const SceneObject & other)
{
	// Copy other object's transformation
	m_localTransform = other.m_localTransform;
	// Remove from parent
	m_parent->removeChild(shared_from_this());
	other.m_parent->addChild(shared_from_this());
	return *this;
}


SceneObject::~SceneObject()
{
}

bool SceneObject::addChild(SceneObjectPtr child)
{
	if (!(child->m_parent) && child.get() != this) {
		// If array would be resized, try removing expired references instead
		if (m_children.size() == m_children.capacity()) {
			collectGarbage();
		}
		child->m_parent = SceneObjectPtr(shared_from_this());
		child->setDirty();
		m_children.push_back(SceneObjectWeakPtr(child));
		return true;
	}
	return false;
}

bool SceneObject::removeChild(SceneObjectPtr child)
{
	bool found = false;
	for (std::vector<SceneObjectWeakPtr>::iterator it = m_children.begin(); it != m_children.end(); ++it) {
		// Check if child found
		if ((*it).lock() == child) {
			// Remove child's parent
			child->m_parent.reset();
			child->setDirty();
			// Erase child from m_children
			m_children.erase(it);
			found = true;
			break;
		}
	}
	return found;
}

void SceneObject::setLocalTransform(glm::mat3 local)
{
	m_localTransform = local;
	setDirty();			// Change in transform invalidates subtree's global transform
}

void SceneObject::applyTransform(glm::mat3 transform, bool post)
{
	if (post) {
		m_localTransform = m_localTransform * transform;
	} else {
		m_localTransform = transform * m_localTransform;
	}
	setDirty();			// Change in transform invalidates subtree's global transform
}

void SceneObject::translate(glm::vec2 displacement, bool post)
{
	if (post) {
		m_localTransform = glm::translate(m_localTransform, displacement);
	} else {
		glm::mat3 translate = glm::translate(glm::mat3(1), displacement);
		m_localTransform = translate * m_localTransform;
	}
	setDirty();		// Change in transform invalidates subtree's global transform
}

void SceneObject::globalTranslate(glm::vec2 translate)
{
	// Calculate equivalent local translation
	glm::vec2 localTranslate = translate;
	if (m_parent) {
		localTranslate = (glm::vec2)(glm::vec3(localTranslate.x,localTranslate.y,0) * glm::inverse(m_parent->getGlobalTransform()));
	}
	m_localTransform = glm::translate(glm::mat3(1), localTranslate) * m_localTransform;
	setDirty();
}

void SceneObject::rotate(float angle, bool post)
{
	if (post) {
		m_localTransform = glm::rotate(m_localTransform, angle);
	} else{
		glm::mat3 rotation = glm::rotate(glm::mat3(1), angle);
	}
	setDirty();		// Change in transform invalidates subtree's global transform
}


glm::mat3 SceneObject::getLocalTransform()
{
	return m_localTransform;
}

glm::mat3 SceneObject::getGlobalTransform()
{
	// Recalculate if current global is invalid
	if (dirtyGlobal) {
		calculateGlobalTransform();
	}
	return m_globalTransform;
}

void SceneObject::setDirty()
{
	dirtyGlobal = true;
	for (SceneObjectWeakPtr child : m_children) {
		SceneObjectPtr strongChild = child.lock();
		if (strongChild) {
			strongChild->setDirty();
		}
	}
}

void SceneObject::collectGarbage()
{
	m_children.erase(std::remove_if(m_children.begin(), m_children.end(), 
		[](SceneObjectWeakPtr s) {return s.expired(); }), m_children.end());
}

void SceneObject::calculateGlobalTransform()
{
	if (m_parent.get() == nullptr) {
		// If root, global is local
		m_globalTransform = m_localTransform;
	} else {
		m_globalTransform = m_parent->getGlobalTransform() * m_localTransform;
	}
	dirtyGlobal = false;
}
