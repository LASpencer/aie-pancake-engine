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
	m_2dRenderer = new aie::Renderer2D();
	m_resourceManager = std::make_unique<ResourceManager>();
	m_entityFactory = std::make_unique<EntityFactory>(this);
	m_sceneRoot = std::make_shared<SceneObject>();

	std::vector<std::vector<int>> tileIDs =
	{ {0,2,0,0,0,2,0,0,0},
	{ 0,0,0,2,0,0,0,0,0 },
	{ 2,0,0,1,1,1,2,1,2 },
	{ 0,0,0,0,1,2,0,0,0 },
	{ 2,0,0,1,1,0,0,2,0 },
	{ 0,2,2,1,0,0,0,2,0 },
	{ 0,0,0,2,0,0,2,0,0 },
	{ 0,0,1,1,2,1,0,0,0 },
	{ 1,1,1,1,1,1,1,2,0 },
	{ 0,0,0,0,0,1,1,0,0 },
	{ 0,0,0,2,2,2,0,0,0 },
	{ 0,0,1,0,0,2,0,0,0 },
	{ 2,2,2,0,0,0,0,2,0 },
	{ 0,0,1,0,1,1,2,0,0 },
	{ 0,1,1,1,1,0,0,0,2 },
	{ 0,0,0,0,1,2,2,0,0 } };

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

	//TODO move out to some factory class
	std::shared_ptr<SequenceBehaviour> tankBehaviour(new SequenceBehaviour());
	BehaviourPtr isTank(new AgentIsTankQuestion());
	std::shared_ptr<SelectorBehaviour> pickTankBehaviour(new SelectorBehaviour());
	std::shared_ptr<SequenceBehaviour> deathSequence(new SequenceBehaviour());
	std::shared_ptr<SequenceBehaviour> fleeDangerSequence(new SequenceBehaviour());
	std::shared_ptr<SequenceBehaviour> attackSequence(new SequenceBehaviour());
	std::shared_ptr<SequenceBehaviour> refuelSequence(new SequenceBehaviour());
	std::shared_ptr<SelectorBehaviour> getFuel(new SelectorBehaviour());
	BehaviourPtr isDead(new IsDeadQuestion());
	BehaviourPtr deathBehaviour(new DeathBehaviour());
	BehaviourPtr isInDanger(new OutnumberedQuestion());
	BehaviourPtr fleeDanger(new FleeDanger());
	BehaviourPtr canAttack(new TargetInRangeQuestion(100.f));	//TODO add also a question checking if it can shoot
	BehaviourPtr attackEnemy(new AttackTarget());
	BehaviourPtr isFuelLow(new FuelTooLowQuestion());
	BehaviourPtr refuel(new RefuelBehaviour());
	BehaviourPtr goToBase(new GoToBase());
	BehaviourPtr wander(new Wander());

	std::shared_ptr<LogBehaviour> loggedTankBehaviour(new LogBehaviour(BehaviourPtr(tankBehaviour->clone()), "Tank Behaviour"));
	std::shared_ptr<LogBehaviour> loggedisTank(new LogBehaviour(BehaviourPtr(isTank->clone()), "Is tank?"));
	std::shared_ptr<LogBehaviour> loggedPickBehaviour(new LogBehaviour(BehaviourPtr(pickTankBehaviour->clone()), "Select Tank Behaviour"));
	std::shared_ptr<LogBehaviour> loggedDeathSequence(new LogBehaviour(BehaviourPtr(deathSequence->clone()), "Death Sequence"));
	std::shared_ptr<LogBehaviour> loggedFleeDangerSequence(new LogBehaviour(BehaviourPtr(fleeDangerSequence->clone()), "Flee Danger Sequence"));
	std::shared_ptr<LogBehaviour> loggedAttackSequence(new LogBehaviour(BehaviourPtr(attackSequence->clone()), "Attack Sequence"));
	std::shared_ptr<LogBehaviour> loggedRefuelSequence(new LogBehaviour(BehaviourPtr(refuelSequence->clone()), "Refuel Sequence"));
	std::shared_ptr<LogBehaviour> loggedGetFuel(new LogBehaviour(BehaviourPtr(getFuel->clone()), "Get Fuel"));
	std::shared_ptr<LogBehaviour> loggedIsDead(new LogBehaviour(BehaviourPtr(isDead->clone()), "Am I dead?"));
	std::shared_ptr<LogBehaviour> loggedDeathBehaviour(new LogBehaviour(BehaviourPtr(deathBehaviour->clone()), "Death Behaviour"));
	std::shared_ptr<LogBehaviour> loggedIsInDanger(new LogBehaviour(BehaviourPtr(isInDanger->clone()), "Am I outnumbered?"));
	//TODO finish off

	deathSequence->addChild(isDead);
	deathSequence->addChild(deathBehaviour);
	fleeDangerSequence->addChild(isInDanger);
	fleeDangerSequence->addChild(fleeDanger);
	attackSequence->addChild(canAttack);
	attackSequence->addChild(attackEnemy);
	refuelSequence->addChild(isFuelLow);
	getFuel->addChild(refuel);
	getFuel->addChild(goToBase);
	refuelSequence->addChild(getFuel);

	pickTankBehaviour->addChild(deathSequence);
	pickTankBehaviour->addChild(fleeDangerSequence);
	pickTankBehaviour->addChild(attackSequence);
	pickTankBehaviour->addChild(refuelSequence);
	pickTankBehaviour->addChild(wander); //TODO pick something else?

	tankBehaviour->addChild(isTank);
	tankBehaviour->addChild(pickTankBehaviour);

	//TODO logged version of this
	

	// Place bases
	m_redBase = m_entityFactory->createEntity(EntityFactory::red_base, glm::translate(glm::mat3(1), red_base_pos));
	m_blueBase = m_entityFactory->createEntity(EntityFactory::blue_base, glm::translate(glm::mat3(1), blue_base_pos));


	EntityPtr player = m_entityFactory->createEntity(EntityFactory::blue_tank, glm::translate(glm::mat3(1), glm::vec2(500,500)));
	AgentPtr playerAgent = std::dynamic_pointer_cast<Agent>(player->getComponent(Component::agent));
	//playerAgent->setBehaviour(std::make_shared<KeyboardController>());

	//pathfinding
	playerAgent->setBehaviour(std::make_shared<PathfindingBehaviour>());
	//playerAgent->setMaxVelocity(50.f);

	// Spawn a bunch of wandering cars

	for (int i = 0; i < 10; ++i) {
		EntityPtr wanderer = m_entityFactory->createEntity(EntityFactory::red_tank, glm::translate(glm::mat3(1), glm::vec2(100 + 30*i, 300 + 20*i)));
		AgentPtr wanderAgent = std::dynamic_pointer_cast<Agent>(wanderer->getComponent(Component::agent));
		//wanderAgent->setMaxVelocity(50.f);
		auto isCar = [](Agent* agent) {	EntityPtr entity(agent->getEntity());
										return (bool)(entity->getTagMask() & Entity::ETag::car); };
		wanderAgent->setBehaviour(BehaviourPtr(tankBehaviour->clone()));
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
	if (input->wasKeyPressed(aie::INPUT_KEY_ESCAPE)) {
		quit();
	}

	//HACK for testing pathfinding
	if (input->wasKeyPressed(aie::INPUT_KEY_R)) {
		m_startPos.reset();
		m_path = std::stack<GridSquarePtr>();
	}
	if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT)) {
		GridSquarePtr clickedSquare = m_mapGraph->getSquare(glm::vec2(input->getMouseX(), input->getMouseY()));
		if (m_startPos) {
			m_path = m_mapGraph->findPath(m_startPos, clickedSquare);
		} else {
			m_startPos = clickedSquare;
		}
	}
	//

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
	m_mapGraph->draw(m_2dRenderer);
	drawEntities();

	if (m_startPos) {
		m_2dRenderer->setRenderColour(0x8000ffff);
		glm::vec2 position = m_startPos->getPosition();
		m_2dRenderer->drawCircle(position.x, position.y, 10.f);
		if (!m_path.empty()) {
			m_2dRenderer->setRenderColour(0x0000ffff);
			glm::vec2 previous = position;
			std::stack<GridSquarePtr> pathCopy = m_path;
			while (!pathCopy.empty()) {
				GridSquarePtr nextSquare = pathCopy.top();
				pathCopy.pop();
				glm::vec2 current = nextSquare->getPosition();
				m_2dRenderer->drawLine(previous.x, previous.y, current.x, current.y, 5.f);
				previous = current;
			}
		}
	}

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
	//TODO test collisions vs terrain
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
	entitiesWithComponent = Entity::getEntitiesWithComponent(Component::agent, m_entityList);
	for (EntityPtr entity : entitiesWithComponent) {
		entity->getComponent(Component::agent)->draw(m_2dRenderer);
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


