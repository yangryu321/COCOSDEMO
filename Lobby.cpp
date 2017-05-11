//
//  Lobby.cpp
//  doodler
//
//  Created by mac on 2016-09-05.
//
//

#include "Lobby.hpp"
#include "DrawingCanvas.hpp"
#include "SceneManager.hpp"


bool Lobby::init()
{
    if(! Node::init())
        return false;
    
    
    backGround=LayerColor::create(Color4B(255, 255, 255, 255));
    addChild(backGround);
    
    return true;
    
    
}

void Lobby::onEnter()
{
    Node::onEnter();
    setupUI();
}




void Lobby::setupUI()
{
    
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Sprite* logo = Sprite::create("doodlerLogo.png");
    logo->setAnchorPoint(Vec2(0.5f, 0.5f));
    logo->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.75f));
    this->addChild(logo);
    
    
    ui::Button * soloButton=ui::Button::create();
    soloButton->setAnchorPoint(Vec2(0.5, 0.5));
    soloButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height * 0.4f));
    soloButton->loadTextures("soloButton.png","soloButtonPressed.png");
    soloButton->addTouchEventListener(CC_CALLBACK_2(Lobby::soloPressed, this));
    this->addChild(soloButton);
    
    ui::Button * multiButton=ui::Button::create();
    multiButton->setAnchorPoint(Vec2(0.5, 0.5));
    multiButton->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.25f));
    multiButton->loadTextures("duoButton.png", "duoButtonPressed.png");
    multiButton->addTouchEventListener(CC_CALLBACK_2(Lobby::multiPressed, this));
    this->addChild(multiButton);
    
}



void Lobby::soloPressed(cocos2d::Ref *pSender, ui::Widget::TouchEventType eEventType)
{
    
    if (eEventType == ui::Widget::TouchEventType::ENDED)
    {
        SceneManager::getInstance()->enterSoloGame();

    }
    
    
    
}


void Lobby::multiPressed(cocos2d::Ref *pSender, ui::Widget::TouchEventType eEventType)
{
    
    SceneManager::getInstance()->connectAndEnterNetworkedGame();
    
    
}