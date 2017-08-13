#pragma once
#include "stdafx.h"

#include "Application.h"
#include "Renderer2D.h"
#include "ResourceManager.h"
#include "Entity.h"
#include "EntityFactory.h"
#include "Grid.h"

class GameProjectApp : public aie::Application {
public:
	static const glm::vec2 min_corner;
	static const glm::vec2 max_corner;

	GameProjectApp();
	virtual ~GameProjectApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	void updateEntities(float deltaTime);

	void drawEntities();

	ResourceManager* getResourceManager();
	EntityFactory* getEntityFactory();
	SceneObjectPtr getSceneRoot();
	std::vector<EntityPtr>& getEntityList();
	Grid* getGrid();

protected:
	aie::Renderer2D*	m_2dRenderer;
	std::unique_ptr<ResourceManager>	m_resourceManager;
	std::vector<EntityPtr>	m_entityList;	// Currently active entities in game
	std::unique_ptr<EntityFactory>		m_entityFactory;
	SceneObjectPtr		m_sceneRoot;		// Root node of scene graph
	std::unique_ptr<Grid>				m_mapGraph;

	bool m_showFPS;							// When true, displays fps in corner of screen
};