//
//  SceneManager.cpp
//  doodler
//
//  Created by mac on 2016-09-18.
//
//

#include "SceneManager.hpp"

static SceneManager* sharedSceneManager = nullptr;


SceneManager* SceneManager::getInstance()
{
    
    if (! sharedSceneManager)
    {
        sharedSceneManager = new SceneManager();
    }
    
    return sharedSceneManager;
}







void SceneManager::stateChanged(ConnectionState state)
{
    switch (state)
    {
        case ConnectionState::NOT_CONNECTED:
            CCLOG("Not Connected");
            break;
            
        case ConnectionState::CONNECTING:
            CCLOG("Connecting...");
            break;
            
        case ConnectionState::CONNECTED:
            CCLOG("Connected!");
            break;
    }
    
    if (!drawingCanvas)
    {
        this->loadDrawingScene(true);
    }
    
    
    
}

SceneManager::SceneManager()
{
    
    drawingCanvas = nullptr;
    netWorkingWrapper= new NetworkingWrapper();// STEP 2
    netWorkingWrapper->setDelegate(this);// STEP 3
    
    
    
}


SceneManager::~SceneManager()
{
    
    delete netWorkingWrapper;
    
}

void SceneManager::enterSoloGame()
{
    
    this->loadDrawingScene(false);
    
}

void SceneManager::returnToLobby()
{
    
    
    if (drawingCanvas!=nullptr) {
        Director::getInstance()->popScene();
        drawingCanvas=nullptr;
    }
    
    
}


void SceneManager::loadDrawingScene(bool networked)
{
    auto scene = Scene::create();
    
    drawingCanvas = DrawingCanvas::create();
    drawingCanvas->setNetworkedSession(networked);
    
    scene->addChild(drawingCanvas);
    
    Director::getInstance()->pushScene(scene);
    
    
}



void SceneManager::connectAndEnterNetworkedGame()
{
    
    netWorkingWrapper->attemptToJoinGame();

    
}



void SceneManager::sendData(const void *data, unsigned long length)
{
    
    netWorkingWrapper->sendData(data, length);
}




void SceneManager::receivedData(const void* data, unsigned long length)
{
    
    if (drawingCanvas)
    {
        drawingCanvas->receivedData(data, length);
    }
}








