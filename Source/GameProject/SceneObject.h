#pragma once
#include "stdafx.h"
#include "Component.h"

class SceneObject;
typedef std::shared_ptr<SceneObject> SceneObjectPtr;
typedef std::weak_ptr<SceneObject> SceneObjectWeakPtr;

/*	Object representing a location in a scene graph
	Each SceneObject holds weak references to its children, and
	a shared_ptr to its parent. So, even if no other objects refer
	to it, a SceneObject will continue to exist as long as any 
	descendants require it.

	To minimise the number of matrix calculations performed, the dirty
	flag pattern is used. Whenever the local transform of a 
	SceneObject is changed, it and all descendants have their 
	dirtyGlobal flag enabled. Their global transform will not be 
	recalculated until accessed, and the flag wil then be unset.
	*/
class SceneObject : public std::enable_shared_from_this<SceneObject>
{
public:
	SceneObject();

	SceneObject(glm::mat3 localTransform, SceneObjectPtr parent = SceneObjectPtr());
	
	// Copies local transform and parent
	SceneObject(const SceneObject& other);

	// Copies local transform and moves to other's parent
	SceneObject& operator=(const SceneObject& other);

	virtual ~SceneObject();

	/** Adds new child to this object 
	*	@param child new child to add
	*	@return true if successfully added*/
	bool addChild(SceneObjectPtr child);

	/** Remove child from this object
	*	@param child reference to child to be removed
	*	@return true if removed, false if not found*/
	bool removeChild(SceneObjectPtr child);

	// Sets local 
	void setLocalTransform(glm::mat3 local);

	/** Applies transformation to local transform
	*	@param transform transformation matrix to apply
	*	@param post whether transform is applied after or before current local transform*/
	void applyTransform(glm::mat3 transform, bool post = true);

	/** Translate local transform
	*	@param translate vector to translate by
	*	@param post whether to translate after or before current transformation*/
	void translate(glm::vec2 translate, bool post = true);

	/** Rotate local transform
	*	@param angle angle of rotation in radians
	*	@param post whether to rotate after or before current transformation*/
	void rotate(float angle, bool post = true);

	glm::mat3 getLocalTransform();

	/** Gets global transform, recalculating it if necessary
	*	@return global transform matrix of this scene object*/
	glm::mat3 getGlobalTransform();

	// Sets dirty global flag on this and all descendants
	void setDirty();

	// Erases any expired references in m_children
	void collectGarbage();

protected:
	SceneObjectPtr m_parent;
	std::vector<SceneObjectWeakPtr> m_children;
	glm::mat3 m_localTransform;
	glm::mat3 m_globalTransform;

	bool dirtyGlobal;				//Set to true when globalTransform must be recalculated

	void calculateGlobalTransform();
};

