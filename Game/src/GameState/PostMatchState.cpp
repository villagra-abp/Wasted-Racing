#include "PostMatchState.h"

void PostMatchState::init() {
    //Bind all managers that are going to be used
    eventManager  = &EventManager::getInstance();
    inputManager  = &InputManager::getInstance();
    renderManager = &RenderManager::getInstance();
    objectManager = &ObjectManager::getInstance();
    audioManager = &AudioManager::getInstance();
    physicsManager = &PhysicsManager::getInstance();
    waypointManager = &WaypointManager::getInstance();
    aiManager = &AIManager::getInstance();
    sensorManager = &SensorManager::getInstance();

    GlobalVariables::getInstance().setIgnoreInput(true);
    Game::getInstance().setAccumulatedTime(0);
}

void PostMatchState::update(float &accumulatedTime) {
    //Update input manager

    inputManager->update();

    physicsManager->update(accumulatedTime);

    aiManager->update(accumulatedTime);

    waypointManager->update(accumulatedTime);

    sensorManager->update();
    
    //Update audio manager
    audioManager->update();

    //Event manager has to be the last to be updated
    eventManager->update();

    //Sets if the game keeps running or not
    //:::>Change with event that closes the game
    Game::getInstance().setStay(objectManager->getGameRunning());
}

void PostMatchState::draw() {
    renderManager->draw();
}

void PostMatchState::close() {
    
}