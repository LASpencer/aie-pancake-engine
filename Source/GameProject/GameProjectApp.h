#pragma once
#include "stdafx.h"

#include "Application.h"
#include "Renderer2D.h"
#include "ResourceManager.h"
#include "Entity.h"
#include "EntityFactory.h"
#include "Grid.h"
#include "Agent.h"
#include "VehicleAgent.h"

class GameProjectApp : public aie::Application {
public:
	static const glm::vec2 min_corner;
	static const glm::vec2 max_corner;
	static const glm::vec2 red_base_pos;
	static const glm::vec2 blue_base_pos;

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
	
	std::vector<VehiclePtr>& getTeam(Team team);

	EntityPtr getBase(Team team);

protected:
	aie::Renderer2D*	m_2dRenderer;
	std::unique_ptr<ResourceManager>	m_resourceManager;
	std::vector<EntityPtr>	m_entityList;	// Currently active entities in game
	std::unique_ptr<EntityFactory>		m_entityFactory;
	SceneObjectPtr		m_sceneRoot;		// Root node of scene graph
	std::unique_ptr<Grid>				m_mapGraph;
	std::vector<GridSquarePtr>			m_impassableSquares;
	std::vector<VehiclePtr>				m_blueTeam;
	std::vector<VehiclePtr>				m_redTeam;
	EntityPtr							m_blueBase;
	EntityPtr							m_redBase;
	std::vector<EntityPtr>				m_depots;

	//HACK for testing pathfinding
	GridSquarePtr m_startPos;
	std::stack<GridSquarePtr> m_path;

	bool m_showFPS;							// When true, displays fps in corner of screen
};