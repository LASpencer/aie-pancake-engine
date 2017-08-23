#include "stdafx.h"
#include "gl_core_4_4.h"
#include "GameProjectApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Filepaths.h"
#include "Collider.h"

#include "WeightedSteeringForce.h"
#include "WanderForce.h"
#include "BoundsForce.h"
#include "AvoidTerrainForce.h"
#include "Flocking.h"

#include "TankBehaviour.h"
#include "LogBehaviour.h"

#include "imgui.h"

const glm::vec2 GameProjectApp::min_corner = glm::vec2(0);
const glm::vec2 GameProjectApp::max_corner = glm::vec2(1280, 720);
const glm::vec2 GameProjectApp::red_base_pos = glm::vec2(1180, 600);
const glm::vec2 GameProjectApp::blue_base_pos = glm::vec2(140, 120);

GameProjectApp::GameProjectApp() : m_entityList()
{

}

GameProjectApp::~GameProjectApp() {
}

bool GameProjectApp::startup() {

	m_showFPS = true;
	m_showPaths = false;
	m_2dRenderer = new aie::Renderer2D();
	m_resourceManager = std::make_unique<ResourceManager>();
	m_entityFactory = std::make_unique<EntityFactory>(this);
	m_sceneRoot = std::make_shared<SceneObject>();

	std::vector<std::vector<int>> tileIDs =
	{ {0,1,0,0,0,2,0,0,0},
	{ 0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,1,1,1,2,1,2 },
	{ 0,0,0,0,1,2,0,0,0 },
	{ 2,0,1,0,0,0,2,0,0 },
	{ 0,0,1,0,0,0,2,0,0 },
	{ 0,0,1,1,0,0,2,2,2 },
	{ 0,0,2,0,0,1,1,0,0 },
	{ 0,0,2,0,0,0,1,1,0 },
	{ 0,0,0,2,0,0,0,0,0 },
	{ 1,1,0,2,0,0,0,0,0 },
	{ 1,1,1,2,2,0,0,0,0 },
	{ 1,2,2,0,0,0,0,2,0 },
	{ 1,1,1,0,0,0,0,0,0 },
	{ 0,1,1,1,1,0,0,0,0 },
	{ 0,0,0,0,1,0,0,0,0 } };

	std::vector<std::vector<TileType>> tiles;
	for (std::vector<int> column : tileIDs) {
		std::vector<TileType> tileCol;
		for (int id : column) {
			tileCol.push_back(TileType(id));
		}
		tiles.push_back(tileCol);
	}

	m_mapGraph = std::make_unique<Grid>(tiles);

	m_impassableSquares = m_mapGraph->getImpassableSquares();

	// Create tank behaviour tree
	std::shared_ptr<SequenceBehaviour> tankBehaviour(new SequenceBehaviour());
	BehaviourPtr isTank(new AgentIsTankQuestion());
	std::shared_ptr<SelectorBehaviour> pickTankBehaviour(new SelectorBehaviour());
	std::shared_ptr<SequenceBehaviour> deathSequence(new SequenceBehaviour());
	std::shared_ptr<SequenceBehaviour> fleeDangerSequence(new SequenceBehaviour());
	std::shared_ptr<SequenceBehaviour> refuelSequence(new SequenceBehaviour());
	std::shared_ptr<SelectorBehaviour> getFuel(new SelectorBehaviour());
	std::shared_ptr<SequenceBehaviour> refuelAtBaseSequence(new SequenceBehaviour());
	std::shared_ptr<SequenceBehaviour> blueGoToMouseSequence(new SequenceBehaviour());
	std::shared_ptr<SequenceBehaviour> chaseTargetSequence(new SequenceBehaviour());
	std::shared_ptr<SequenceBehaviour> flockAndWander(new SequenceBehaviour());

	BehaviourPtr isDead(new IsDeadQuestion());
	BehaviourPtr deathBehaviour(new DeathBehaviour());
	BehaviourPtr isInDanger(new OutnumberedQuestion());
	BehaviourPtr fleeDanger(new FleeDanger());
	BehaviourPtr attackEnemy(new AttackTarget());
	BehaviourPtr isFuelLow(new FuelTooLowQuestion());
	BehaviourPtr refuel(new RefuelBehaviour());
	BehaviourPtr isAtBase(new AtBaseQuestion());
	BehaviourPtr goToBase(new GoToBase());
	BehaviourPtr isBlueTank(new IsBlueQuestion());
	BehaviourPtr moveToMouse(new MoveToHeldMouse());
	BehaviourPtr targetInRange(new TargetInRangeQuestion(200.f));
	BehaviourPtr chaseTarget(new ChaseTarget());
	BehaviourPtr wander(new Wander());
	BehaviourPtr flock(new Flocking());

	deathSequence->addChild(isDead);
	deathSequence->addChild(deathBehaviour);
	fleeDangerSequence->addChild(isInDanger);
	fleeDangerSequence->addChild(fleeDanger);
	refuelSequence->addChild(isFuelLow);
	refuelAtBaseSequence->addChild(isAtBase);
	refuelAtBaseSequence->addChild(refuel);
	getFuel->addChild(refuelAtBaseSequence);
	getFuel->addChild(goToBase);
	refuelSequence->addChild(getFuel);
	blueGoToMouseSequence->addChild(isBlueTank);
	blueGoToMouseSequence->addChild(moveToMouse);
	chaseTargetSequence->addChild(targetInRange);
	chaseTargetSequence->addChild(chaseTarget);
	flockAndWander->addChild(flock);
	flockAndWander->addChild(wander);

	pickTankBehaviour->addChild(deathSequence);
	pickTankBehaviour->addChild(fleeDangerSequence);
	pickTankBehaviour->addChild(attackEnemy);
	pickTankBehaviour->addChild(refuelSequence);
	pickTankBehaviour->addChild(blueGoToMouseSequence);
	pickTankBehaviour->addChild(chaseTargetSequence);
	pickTankBehaviour->addChild(flockAndWander); //TODO pick something else?

	tankBehaviour->addChild(isTank);
	tankBehaviour->addChild(pickTankBehaviour);

	// Place bases
	m_redBase = m_entityFactory->createEntity(EntityFactory::red_base, glm::translate(glm::mat3(1), red_base_pos));
	m_blueBase = m_entityFactory->createEntity(EntityFactory::blue_base, glm::translate(glm::mat3(1), blue_base_pos));


	// Spawn a bunch of tanks

	for (int i = 0; i < 5; ++i) {
		EntityPtr tank = m_entityFactory->createEntity(EntityFactory::blue_tank, glm::translate(glm::mat3(1), glm::vec2(200,50*i)));
		AgentPtr tankAgent = std::dynamic_pointer_cast<Agent>(tank->getComponent(Component::agent));
		tankAgent->setBehaviour(BehaviourPtr(tankBehaviour->clone()));
	}

	for (int i = 0; i < 5; ++i) {
		EntityPtr tank = m_entityFactory->createEntity(EntityFactory::red_tank, glm::translate(glm::mat3(1), glm::vec2(1000 , 700 - 50 * i)));
		AgentPtr tankAgent = std::dynamic_pointer_cast<Agent>(tank->getComponent(Component::agent));
		tankAgent->setBehaviour(BehaviourPtr(tankBehaviour->clone()));
	}
	
	// Disable face culling, so sprites can be flipped
	glDisable(GL_CULL_FACE);
	return true;
}

void GameProjectApp::shutdown() {

	// Release any surviving shared pointers
	m_entityList.clear();
	m_sceneRoot.reset();
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
	if (input->wasKeyPressed(aie::INPUT_KEY_P)) {
		m_showPaths = !m_showPaths;
	}
	if (input->wasKeyPressed(aie::INPUT_KEY_N)) {
		m_mapGraph->toggleShowNodes();
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
	m_mapGraph->draw(m_2dRenderer);
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
	//Move the agents
	for (EntityPtr entity : entitiesWithComponent) {
		std::dynamic_pointer_cast<Agent>(entity->getComponent(Component::agent))->moveAgent(deltaTime);
	}

	// Assign entities to grid squares
	m_mapGraph->placeEntities(m_entityList);

	// Update colliders
	entitiesWithComponent = Entity::getEntitiesWithComponent(Component::collider, m_entityList);
	std::vector<ColliderPtr> colliders;
	for (EntityPtr entity : entitiesWithComponent) {
		std::shared_ptr<Collider> collider = std::dynamic_pointer_cast<Collider>(entity->getComponent(Component::collider));
		collider->update(deltaTime);
		colliders.push_back(collider);
	}
	// Resolve collisions
	Collider::resolveCollisions(colliders, m_impassableSquares);

}

void GameProjectApp::drawEntities()
{
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
	if (m_showPaths) {
		entitiesWithComponent = Entity::getEntitiesWithComponent(Component::agent, m_entityList);
		for (EntityPtr entity : entitiesWithComponent) {
			entity->getComponent(Component::agent)->draw(m_2dRenderer);
		}
	}
}

ResourceManager * GameProjectApp::getResourceManager()
{
	return m_resourceManager.get();
}

EntityFactory * GameProjectApp::getEntityFactory()
{
	return m_entityFactory.get();
}

SceneObjectPtr GameProjectApp::getSceneRoot()
{
	return m_sceneRoot;
}

std::vector<EntityPtr>& GameProjectApp::getEntityList()
{
	return m_entityList;
}

Grid* GameProjectApp::getGrid()
{
	return m_mapGraph.get();
}

std::vector<VehiclePtr>& GameProjectApp::getTeam(Team team)
{
	if (team == red) {
		return m_redTeam;
	}
	else {
		return m_blueTeam;
	}
}

EntityPtr GameProjectApp::getBase(Team team)
{
	if (team == red) {
		return m_redBase;
	}
	else {
		return m_blueBase;
	}
}


