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
#include "GuardExerciseBehaviour.h"
#include "AvoidForce.h"

#include "imgui.h"

const glm::vec2 GameProjectApp::min_corner = glm::vec2(0);
const glm::vec2 GameProjectApp::max_corner = glm::vec2(1280, 720);

GameProjectApp::GameProjectApp() : m_entityList()
{

}

GameProjectApp::~GameProjectApp() {
}

bool GameProjectApp::startup() {

	m_showFPS = true;
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

	m_mapGraph.addEdge(0, 1, 200);
	m_mapGraph.addEdge(0, 5, 400);
	m_mapGraph.addEdge(1, 2, 150);
	m_mapGraph.addEdge(2, 0, 250);
	m_mapGraph.addEdge(2, 3, 150);
	m_mapGraph.addEdge(2, 6, 200);
	m_mapGraph.addEdge(3, 4, 180);
	m_mapGraph.addEdge(3, 5, 200);
	m_mapGraph.addEdge(4, 0, 460);
	m_mapGraph.addEdge(5, 4, 180);
	m_mapGraph.addEdge(6, 3, 280);

	EntityPtr player = m_entityFactory->createEntity(EntityFactory::car, glm::translate(glm::mat3(1), glm::vec2(500,500)));
	AgentPtr playerAgent = std::dynamic_pointer_cast<Agent>(player->getComponent(Component::agent));
	playerAgent->addBehaviour(std::make_shared<SteeringBehaviour>(std::make_shared<AvoidForce>()));
	playerAgent->addBehaviour(std::make_shared<KeyboardController>());


	//pathfinding
	/*playerAgent->addBehaviour(std::make_shared<PathfindingBehaviour>(&m_mapGraph, m_mapGraph.m_graph[0]));
	playerAgent->setMaxVelocity(50.f);*/

	//EntityPtr car = m_entityFactory->createEntity(EntityFactory::car, glm::translate(glm::mat3(1), glm::vec2(800, 300)));
	//AgentPtr carAgent = std::dynamic_pointer_cast<Agent>(car->getComponent(Component::agent));
	//carAgent->setMaxVelocity(150.f);
	//carAgent->addBehaviour(std::make_shared<SteeringBehaviour>(std::make_shared<AvoidForce>()));
	////HACK
	//BehaviourPtr stayinBounds = std::make_shared<SteeringBehaviour>(std::make_shared<BoundsForce>());
	//carAgent->addBehaviour(stayinBounds);

	//// guard car uses decision tree
	//
	//carAgent->addBehaviour(std::make_shared<GuardExerciseBehaviour>(std::make_shared<EntityTarget>(player)));

	m_entityFactory->createEntity(EntityFactory::block, glm::translate(glm::mat3(1), glm::vec2(300, 300)));
	m_entityFactory->createEntity(EntityFactory::block, glm::translate(glm::mat3(1), glm::vec2(300, 200)));
	m_entityFactory->createEntity(EntityFactory::block, glm::translate(glm::mat3(1), glm::vec2(300, 100)));

	m_entityFactory->createEntity(EntityFactory::block, glm::translate(glm::mat3(1), glm::vec2(450, 300)));
	m_entityFactory->createEntity(EntityFactory::block, glm::translate(glm::mat3(1), glm::vec2(450, 200)));
	m_entityFactory->createEntity(EntityFactory::block, glm::translate(glm::mat3(1), glm::vec2(450, 100)));

	// Spawn a bunch of wandering cars

	for (int i = 0; i < 50; ++i) {
		EntityPtr wanderer = m_entityFactory->createEntity(EntityFactory::car, glm::translate(glm::mat3(1), glm::vec2(640, 360)));
		AgentPtr wanderAgent = std::dynamic_pointer_cast<Agent>(wanderer->getComponent(Component::agent));
		wanderAgent->setMaxVelocity(50.f);
		std::shared_ptr<WeightedSteeringForce> wanderInBounds = std::make_shared<WeightedSteeringForce>();
		wanderInBounds->addForce(std::make_shared<BoundsForce>(), 1.f);
		//wanderInBounds->addForce(std::make_shared<AvoidForce>(), 0.8f);
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
	if (input->wasKeyPressed(aie::INPUT_KEY_GRAVE_ACCENT)) {
		Collider::setDrawBoxes(!Collider::draw_boxes);
	}
	if (input->wasKeyPressed(aie::INPUT_KEY_ESCAPE)) {
		quit();
	}

	updateEntities(deltaTime);

	//HACK
	ImGui::Begin("Test");
	ImGui::Text("Hello, world!");
	//ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
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
	//Update agent components
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
	entitiesWithComponent = Entity::getEntitiesWithComponent(Component::agent, m_entityList);
	for (EntityPtr entity : entitiesWithComponent) {
		entity->getComponent(Component::agent)->draw(m_2dRenderer);
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

