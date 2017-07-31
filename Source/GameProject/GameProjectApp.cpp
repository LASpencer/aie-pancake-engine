#include "stdafx.h"
#include "gl_core_4_4.h"
#include "GameProjectApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Filepaths.h"
#include "Collider.h"

#include "FSMBehaviour.h"
#include "GuardStateMachine.h"
#include "KeyboardController.h"
#include "WeightedSteeringForce.h"
#include "SteeringBehaviour.h"
#include "WanderForce.h"
#include "BoundsForce.h"
#include "PathfindingBehaviour.h"

GameProjectApp::GameProjectApp() : m_entityList()
{

}

GameProjectApp::~GameProjectApp() {
}

bool GameProjectApp::startup() {

	m_showFPS = false;
	m_2dRenderer = new aie::Renderer2D();
	m_resourceManager = new ResourceManager();
	m_entityFactory = new EntityFactory(this);
	m_sceneRoot = std::make_shared<SceneObject>();

	//HACK figure out a less ugly way to make graphs
	m_mapGraph.addNode({ 200,600 });
	m_mapGraph.addNode({ 400,600 });
	m_mapGraph.addNode({ 400,450 });
	m_mapGraph.addNode({ 400,300 });
	m_mapGraph.addNode({ 300,150 });
	m_mapGraph.addNode({ 200,300 });
	m_mapGraph.addNode({600, 500});

	m_mapGraph.addEdge(0, 1, 2);
	m_mapGraph.addEdge(0, 5, 5);
	m_mapGraph.addEdge(1, 2, 3);
	m_mapGraph.addEdge(2, 0, 3);
	m_mapGraph.addEdge(2, 3, 1);
	m_mapGraph.addEdge(2, 6, 5);
	m_mapGraph.addEdge(3, 4, 4);
	m_mapGraph.addEdge(3, 5, 4);
	m_mapGraph.addEdge(4, 0, 99);
	m_mapGraph.addEdge(5, 4, 6);
	m_mapGraph.addEdge(6, 3, 7);

	EntityPtr player = m_entityFactory->createEntity(EntityFactory::car, glm::translate(glm::mat3(1), glm::vec2(500,500)));
	AgentPtr playerAgent = std::dynamic_pointer_cast<Agent>(player->getComponent(Component::agent));
	playerAgent->addBehaviour(std::make_shared<PathfindingBehaviour>(&m_mapGraph, m_mapGraph.m_graph[0]));
	playerAgent->setMaxVelocity(50.f);

	//EntityPtr car = m_entityFactory->createEntity(EntityFactory::car, glm::translate(glm::mat3(1), glm::vec2(100, 100)));
	////set guard car agent's behaviour as fsm behaviour with guard state machine
	//AgentPtr carAgent = std::dynamic_pointer_cast<Agent>(car->getComponent(Component::agent));
	//GuardStateMachine* guardMachine = new GuardStateMachine({ {80,80},{1000,100},{950,600},{200,650} }, player);
	//guardMachine->forceState(GuardStateMachine::patrol, carAgent.get());
	//std::shared_ptr<FSMBehaviour> guardBehaviour = std::make_shared<FSMBehaviour>(guardMachine);
	//carAgent->addBehaviour(guardBehaviour);
	for (int i = 0; i < 10; ++i) {
		EntityPtr wanderer = m_entityFactory->createEntity(EntityFactory::car, glm::translate(glm::mat3(1), glm::vec2(640, 360)));
		AgentPtr wanderAgent = std::dynamic_pointer_cast<Agent>(wanderer->getComponent(Component::agent));
		wanderAgent->setMaxVelocity(50.f);
		std::shared_ptr<WeightedSteeringForce> wanderInBounds = std::make_shared<WeightedSteeringForce>();
		wanderInBounds->addForce(std::make_shared<BoundsForce>(), 1.f);
		wanderInBounds->addForce(std::make_shared<WanderForce>(), 1.f);
		wanderAgent->addBehaviour(std::make_shared<SteeringBehaviour>(wanderInBounds));
	}
	// Disable face culling, so sprites can be flipped
	glDisable(GL_CULL_FACE);
	return true;
}

void GameProjectApp::shutdown() {

	// Release any surviving shared pointers
	m_entityList.clear();
	m_sceneRoot.reset();
	delete m_entityFactory;
	delete m_resourceManager;
	delete m_2dRenderer;
}

void GameProjectApp::update(float deltaTime) {

	// Toggle fps
	aie::Input* input = aie::Input::getInstance();
	if (input->wasKeyPressed(aie::INPUT_KEY_F)) {
		m_showFPS = !m_showFPS;
	}
	if (input->wasKeyPressed(aie::INPUT_KEY_ESCAPE)) {
		quit();
	}

	updateEntities(deltaTime);
}

void GameProjectApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// Reset UVRect to full texture
	m_2dRenderer->setUVRect(0, 0, 1, 1);

	// Draw game
	drawEntities();

	//fps info
	if (m_showFPS) {
		m_2dRenderer->setRenderColour(1, 1, 0, 1);
		char fps[32];
		sprintf_s(fps, 32, "FPS: %i", getFPS());
		m_2dRenderer->drawText((m_resourceManager->getFont(filepath::consolas_path, 32))->get(), fps, 0, 720 - 32);
	}
	// done drawing sprites
	m_2dRenderer->end();
}

void GameProjectApp::updateEntities(float deltaTime)
{
	//Update controller components
	std::vector<EntityPtr> entitiesWithComponent = Entity::getEntitiesWithComponent(Component::agent, m_entityList);
	for (EntityPtr entity : entitiesWithComponent) {
		entity->getComponent(Component::agent)->update(deltaTime);
	}
	// Update colliders and test collision
	entitiesWithComponent = Entity::getEntitiesWithComponent(Component::collider, m_entityList);
	std::vector<std::shared_ptr<Collider>> colliders;
	for (EntityPtr entity : entitiesWithComponent) {
		std::shared_ptr<Collider> collider = std::dynamic_pointer_cast<Collider>(entity->getComponent(Component::collider));
		collider->update(deltaTime);
		colliders.push_back(collider);
	}
	Collider::resolveCollisions(colliders);
}

void GameProjectApp::drawEntities()
{
	for (MapNode* node : m_mapGraph.m_graph) {
		m_2dRenderer->drawCircle(node->position.x, node->position.y, 15);
		for (MapEdge edge : node->connections) {
			m_2dRenderer->drawLine(node->position.x, node->position.y, edge.target->position.x, edge.target->position.y, 3);
		}
	}
	std::vector<EntityPtr> entitiesWithComponent = Entity::getEntitiesWithComponent(Component::sprite, m_entityList);
	for (EntityPtr entity : entitiesWithComponent) {
		entity->getComponent(Component::sprite)->draw(m_2dRenderer);
	}
	if (Collider::draw_boxes) {
		entitiesWithComponent = Entity::getEntitiesWithComponent(Component::collider, m_entityList);
		for (EntityPtr entity : entitiesWithComponent) {
			entity->getComponent(Component::collider)->draw(m_2dRenderer);
		}
	}
}

ResourceManager * GameProjectApp::getResourceManager()
{
	return m_resourceManager;
}

EntityFactory * GameProjectApp::getEntityFactory()
{
	return m_entityFactory;
}

SceneObjectPtr GameProjectApp::getSceneRoot()
{
	return m_sceneRoot;
}

std::vector<EntityPtr>& GameProjectApp::getEntityList()
{
	return m_entityList;
}

