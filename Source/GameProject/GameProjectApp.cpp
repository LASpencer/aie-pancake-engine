#include "stdafx.h"
#include "gl_core_4_4.h"
#include "GameProjectApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Filepaths.h"
#include "Collider.h"

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
	m_showBehaviourTree = false;
	m_2dRenderer = new aie::Renderer2D();
	m_resourceManager = std::make_unique<ResourceManager>();
	m_entityFactory = std::make_unique<EntityFactory>(this);
	m_sceneRoot = std::make_shared<SceneObject>();

	// Create map
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
	/*	Structure is as follows
		
		tankBehaviour (AND)
			isTank
			pickTankBehaviour (OR)
				deathSequence (AND)
					isDead
					deathBehaviour
				fleeDangerSequence (AND)
					isInDanger
					fleeDanger
				attackEnemy
				refuelSequence (AND)
					isFuelLow
					getFuel (OR)
						refuelAtBaseSequence (AND)
							isAtBase
							refuel
						goToBase
				blueGoToMouseSequence (AND)
					isBlueTank
					moveToMouse
				chaseTargetSequence (AND)
					targetInRange
					chaseTarget
				flockAndWander (AND)
					flock
					wander
	*/
	std::shared_ptr<SequenceBehaviour> tankBehaviour(new SequenceBehaviour());			// Root node
	BehaviourPtr isTank(new AgentIsTankQuestion());										// Checks agent is a tank
	std::shared_ptr<SelectorBehaviour> pickTankBehaviour(new SelectorBehaviour());		// Holds behaviours for tank to choose from, in order
	std::shared_ptr<SequenceBehaviour> deathSequence(new SequenceBehaviour());			// Tank is dead (and will respawn after time)
	std::shared_ptr<SequenceBehaviour> fleeDangerSequence(new SequenceBehaviour());		// Tank flees enemies if outnumbered
	std::shared_ptr<SequenceBehaviour> refuelSequence(new SequenceBehaviour());			// Tank returns to base if fuel is low
	std::shared_ptr<SelectorBehaviour> getFuel(new SelectorBehaviour());				// Refuel if at base, or go to base if not
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

	// Create logged clone of behaviours
	std::shared_ptr<LogBehaviour> loggedTankBehaviour(new LogBehaviour(this, BehaviourPtr(tankBehaviour->clone()), "Tank Behaviour"));
	std::shared_ptr<LogBehaviour> loggedIsTank(new LogBehaviour(this, BehaviourPtr(isTank->clone()), "Is tank?"));
	std::shared_ptr<LogBehaviour> loggedPickBehaviour(new LogBehaviour(this, BehaviourPtr(pickTankBehaviour->clone()), "Select Tank Behaviour"));
	std::shared_ptr<LogBehaviour> loggedDeathSequence(new LogBehaviour(this, BehaviourPtr(deathSequence->clone()), "Death Sequence"));
	std::shared_ptr<LogBehaviour> loggedFleeDangerSequence(new LogBehaviour(this, BehaviourPtr(fleeDangerSequence->clone()), "Flee Danger Sequence"));
	std::shared_ptr<LogBehaviour> loggedRefuelSequence(new LogBehaviour(this, BehaviourPtr(refuelSequence->clone()), "Refuel Sequence"));
	std::shared_ptr<LogBehaviour> loggedBlueGoToMouseSequence(new LogBehaviour(this, BehaviourPtr(refuelSequence->clone()), "Blue Go To Mouse Sequence"));
	std::shared_ptr<LogBehaviour> loggedChaseTargetSequence(new LogBehaviour(this, BehaviourPtr(refuelSequence->clone()), "Chase Target Sequence"));
	std::shared_ptr<LogBehaviour> loggedFlockAndWander(new LogBehaviour(this, BehaviourPtr(flockAndWander->clone()), "Flock and Wander"));

	std::shared_ptr<LogBehaviour> loggedGetFuel(new LogBehaviour(this, BehaviourPtr(getFuel->clone()), "Get Fuel"));
	std::shared_ptr<LogBehaviour> loggedRefuelAtBase(new LogBehaviour(this, BehaviourPtr(refuelAtBaseSequence->clone()), "Get fuel from base"));
	std::shared_ptr<LogBehaviour> loggedIsDead(new LogBehaviour(this, BehaviourPtr(isDead->clone()), "Am I dead?"));
	std::shared_ptr<LogBehaviour> loggedDeathBehaviour(new LogBehaviour(this, BehaviourPtr(deathBehaviour->clone()), "Death Behaviour"));
	std::shared_ptr<LogBehaviour> loggedIsInDanger(new LogBehaviour(this, BehaviourPtr(isInDanger->clone()), "Am I outnumbered?"));
	std::shared_ptr<LogBehaviour> loggedFleeDanger(new LogBehaviour(this, BehaviourPtr(fleeDanger->clone()), "Flee Danger"));
	std::shared_ptr<LogBehaviour> loggedAttackEnemy(new LogBehaviour(this, BehaviourPtr(attackEnemy->clone()), "Attacking Enemy"));
	std::shared_ptr<LogBehaviour> loggedIsFuelLow(new LogBehaviour(this, BehaviourPtr(isFuelLow->clone()), "Is fuel too low?"));
	std::shared_ptr<LogBehaviour> loggedRefuel(new LogBehaviour(this, BehaviourPtr(refuel->clone()), "Refuelling"));
	std::shared_ptr<LogBehaviour> loggedIsAtBase(new LogBehaviour(this, BehaviourPtr(isAtBase->clone()), "Am I at my base?"));
	std::shared_ptr<LogBehaviour> loggedGoToBase(new LogBehaviour(this, BehaviourPtr(goToBase->clone()), "Go to base"));
	std::shared_ptr<LogBehaviour> loggedIsBlue(new LogBehaviour(this, BehaviourPtr(isBlueTank->clone()), "Am I on blue team?"));
	std::shared_ptr<LogBehaviour> loggedMoveToMouse(new LogBehaviour(this, BehaviourPtr(moveToMouse->clone()), "Move to mouse"));
	std::shared_ptr<LogBehaviour> loggedTargetInRange(new LogBehaviour(this, BehaviourPtr(targetInRange->clone()), "Is target in range?"));
	std::shared_ptr<LogBehaviour> loggedChaseTarget(new LogBehaviour(this, BehaviourPtr(chaseTarget->clone()), "ChaseTarget"));
	std::shared_ptr<LogBehaviour> loggedWander(new LogBehaviour(this, BehaviourPtr(wander->clone()), "Wander"));
	std::shared_ptr<LogBehaviour> loggedFlock(new LogBehaviour(this, BehaviourPtr(flock->clone()), "Flock"));

	// Put tree together
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
	pickTankBehaviour->addChild(flockAndWander); 

	tankBehaviour->addChild(isTank);
	tankBehaviour->addChild(pickTankBehaviour);

	// Create logged tree
	std::dynamic_pointer_cast<SequenceBehaviour>(loggedDeathSequence->getBehaviour())->addChild(loggedIsDead);
	std::dynamic_pointer_cast<SequenceBehaviour>(loggedDeathSequence->getBehaviour())->addChild(loggedDeathBehaviour);
	
	std::dynamic_pointer_cast<SequenceBehaviour>(loggedFleeDangerSequence->getBehaviour())->addChild(loggedIsInDanger);
	std::dynamic_pointer_cast<SequenceBehaviour>(loggedFleeDangerSequence->getBehaviour())->addChild(loggedFleeDanger);
	
	std::dynamic_pointer_cast<SequenceBehaviour>(loggedRefuelSequence->getBehaviour())->addChild(loggedIsFuelLow);
	
	std::dynamic_pointer_cast<SequenceBehaviour>(loggedRefuelAtBase->getBehaviour())->addChild(loggedIsAtBase);
	std::dynamic_pointer_cast<SequenceBehaviour>(loggedRefuelAtBase->getBehaviour())->addChild(loggedRefuel);
	
	std::dynamic_pointer_cast<SelectorBehaviour>(loggedGetFuel->getBehaviour())->addChild(loggedRefuelAtBase);
	std::dynamic_pointer_cast<SelectorBehaviour>(loggedGetFuel->getBehaviour())->addChild(loggedGoToBase);
	
	std::dynamic_pointer_cast<SequenceBehaviour>(loggedRefuelSequence->getBehaviour())->addChild(loggedGetFuel);
	
	std::dynamic_pointer_cast<SequenceBehaviour>(loggedBlueGoToMouseSequence->getBehaviour())->addChild(loggedIsBlue);
	std::dynamic_pointer_cast<SequenceBehaviour>(loggedBlueGoToMouseSequence->getBehaviour())->addChild(loggedMoveToMouse);
	
	std::dynamic_pointer_cast<SequenceBehaviour>(loggedChaseTargetSequence->getBehaviour())->addChild(loggedTargetInRange);
	std::dynamic_pointer_cast<SequenceBehaviour>(loggedChaseTargetSequence->getBehaviour())->addChild(loggedChaseTarget);
	
	std::dynamic_pointer_cast<SequenceBehaviour>(loggedFlockAndWander->getBehaviour())->addChild(loggedFlock);
	std::dynamic_pointer_cast<SequenceBehaviour>(loggedFlockAndWander->getBehaviour())->addChild(loggedWander);

	std::dynamic_pointer_cast<SelectorBehaviour>(loggedPickBehaviour->getBehaviour())->addChild(loggedDeathSequence);
	std::dynamic_pointer_cast<SelectorBehaviour>(loggedPickBehaviour->getBehaviour())->addChild(loggedFleeDangerSequence);
	std::dynamic_pointer_cast<SelectorBehaviour>(loggedPickBehaviour->getBehaviour())->addChild(loggedAttackEnemy);
	std::dynamic_pointer_cast<SelectorBehaviour>(loggedPickBehaviour->getBehaviour())->addChild(loggedRefuelSequence);
	std::dynamic_pointer_cast<SelectorBehaviour>(loggedPickBehaviour->getBehaviour())->addChild(loggedBlueGoToMouseSequence);
	std::dynamic_pointer_cast<SelectorBehaviour>(loggedPickBehaviour->getBehaviour())->addChild(loggedChaseTargetSequence);
	std::dynamic_pointer_cast<SelectorBehaviour>(loggedPickBehaviour->getBehaviour())->addChild(loggedFlockAndWander);
	
	std::dynamic_pointer_cast<SequenceBehaviour>(loggedTankBehaviour->getBehaviour())->addChild(loggedIsTank);
	std::dynamic_pointer_cast<SequenceBehaviour>(loggedTankBehaviour->getBehaviour())->addChild(loggedPickBehaviour);
	
	// Place bases
	m_redBase = m_entityFactory->createEntity(EntityFactory::red_base, glm::translate(glm::mat3(1), red_base_pos));
	m_blueBase = m_entityFactory->createEntity(EntityFactory::blue_base, glm::translate(glm::mat3(1), blue_base_pos));


	// Spawn a bunch of tanks

	for (int i = 0; i < 4; ++i) {
		EntityPtr tank = m_entityFactory->createEntity(EntityFactory::blue_tank, glm::translate(glm::mat3(1), glm::vec2(200,50*i)));
		AgentPtr tankAgent = std::dynamic_pointer_cast<Agent>(tank->getComponent(Component::agent));
		tankAgent->setBehaviour(BehaviourPtr(tankBehaviour->clone()));
	}

	// Spawn tank with logged behaviour tree
	EntityPtr tank = m_entityFactory->createEntity(EntityFactory::blue_tank, glm::translate(glm::mat3(1), glm::vec2(200, 200)));
	VehiclePtr tankAgent = std::dynamic_pointer_cast<VehicleAgent>(tank->getComponent(Component::agent));
	tankAgent->setBehaviour(BehaviourPtr(loggedTankBehaviour->clone()));
	m_loggedTank = tankAgent;

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
	// Toggle showing hitboxes
	if (input->wasKeyPressed(aie::INPUT_KEY_GRAVE_ACCENT)) {
		Collider::setDrawBoxes(!Collider::draw_boxes);
	}
	// Toggle showing paths
	if (input->wasKeyPressed(aie::INPUT_KEY_P)) {
		m_showPaths = !m_showPaths;
	}
	// Toggle showing map nodes
	if (input->wasKeyPressed(aie::INPUT_KEY_N)) {
		m_mapGraph->toggleShowNodes();
	}
	// Toggle showing behaviours of loggedTank
	if (input->wasKeyPressed(aie::INPUT_KEY_B)) {
		m_showBehaviourTree = !m_showBehaviourTree;
	}
	if (input->wasKeyPressed(aie::INPUT_KEY_ESCAPE)) {
		quit();
	}

	// Add behaviour tree window if shown
	if (m_showBehaviourTree) {
		ImGui::Begin("Behaviours");
	}
	updateEntities(deltaTime);
	if (m_showBehaviourTree) {
		ImGui::End();
		// Show additional info about logged tank
		ImGui::Begin("Tank Info");
		glm::vec2 pos = m_loggedTank->getPosition();
		glm::vec2 velocity = m_loggedTank->getVelocity();
		glm::vec2 force = m_loggedTank->getForce();
		ImGui::Text("Position (%3.0f, %3.0f)", pos.x, pos.y);
		ImGui::Text("Velocity (%3.0f, %3.0f)", velocity.x, velocity.y);
		ImGui::Text("Force (%3.0f, %3.0f)", force.x, force.y);
		ImGui::Text("Fuel %.0f / %.0f", m_loggedTank->getFuel(), m_loggedTank->getMaxFuel());
		ImGui::End();
	}
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

	// If showing behaviour tree, highlight logged tank
	if (m_showBehaviourTree) {
		glm::vec2 highlightPos = m_loggedTank->getPosition();
		m_2dRenderer->setRenderColour(0.8f, 0, 1, 0.5f);
		m_2dRenderer->drawCircle(highlightPos.x, highlightPos.y, 30.f);
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

bool GameProjectApp::shouldShowBehaviourTree()
{
	return m_showBehaviourTree;
}


