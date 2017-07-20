#include "stdafx.h"
#include "gl_core_4_4.h"
#include "GameProjectApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Filepaths.h"
#include "Collider.h"

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
	//TODO draw bg
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
	std::vector<EntityPtr> entitiesWithComponent = Entity::getEntitiesWithComponent(Component::controller, m_entityList);
	for (EntityPtr entity : entitiesWithComponent) {
		entity->getComponent(Component::controller)->update(deltaTime);
	}
	//Update body components
	std::vector<EntityPtr> entitiesWithComponent = Entity::getEntitiesWithComponent(Component::body, m_entityList);
	for (EntityPtr entity : entitiesWithComponent) {
		entity->getComponent(Component::body)->update(deltaTime);
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

