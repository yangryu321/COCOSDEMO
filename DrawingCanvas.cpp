//
//  DrawingCanvas.cpp
//  doodler
//
//  Created by mac on 2016-09-04.
//
//

#include "DrawingCanvas.hpp"
#include "Lobby.hpp"
#include "SceneManager.hpp"
#include "JSONPacker.hpp"

bool DrawingCanvas::init()
{
    if (! Node::init()) {
        return false;
    }
    backGround=LayerColor::create(Color4B(255, 255, 255, 255));//可以把node 看成是一个透明的画布
    addChild(backGround);
    
    selecetedColor=COLOR_GREEN;
    
    drawNode = DrawNode::create();
    this->addChild(drawNode);
//    backGround=LayerColor::create(Color4B(255, 255, 255, 255));
//    addChild(backGround);
    return true;
    
}



void DrawingCanvas::onEnter()
{
    Node::onEnter();
    
    Size visibelSize=Director::getInstance()->getVisibleSize();
    this->setContentSize(visibelSize);
    drawNode->setContentSize(visibelSize);
    setupTouchHandling();
    setupMenu();
    
}

void DrawingCanvas::setupTouchHandling()
{
    static Vec2 lastTouchPos;
    auto touchListener = EventListenerTouchOneByOne::create();//设置触摸监听器
    static float lastRadius = INITIAL_RADIUS;
    touchListener->onTouchBegan = [&](Touch* touch, Event* event)
    {
        lastTouchPos = drawNode->convertTouchToNodeSpace(touch);
        lastRadius = INITIAL_RADIUS;
        
        return true;
    };
    
    touchListener->onTouchMoved = [&](Touch* touch, Event* event)
    {
        
        Vec2 touchPos = drawNode->convertTouchToNodeSpace(touch);
        float distance = lastTouchPos.distance(touchPos); //为什么画的越快 就越粗
        float dt = 1.0f / 60.0f;
        float rc = 1.0f;
        float alpha = dt / (rc + dt);
        float radius = (alpha * distance) + (1.0f - alpha) * lastRadius;
        drawNode->drawSegment(lastTouchPos, touchPos, radius, selecetedColor);
        
        if (this->networkedSession)
        {
            this->sendStrokeOverNetwork(lastTouchPos, touchPos, radius, selecetedColor);
        }
        
        CCLOG("Touch Moved! x:%f y:%f", touchPos.x, touchPos.y);
 
        lastTouchPos=touchPos;
        lastRadius = radius;
        
    };
    
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    
    
    
}


void DrawingCanvas::setupMenu()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    Node* colorButtonLayout = Node::create();
    colorButtonLayout->setContentSize(Size(visibleSize.width, visibleSize.height * 0.2f));
    colorButtonLayout->setAnchorPoint(Vec2(0.5f, 0.0f));
    colorButtonLayout->setPosition(Vec2(visibleSize.width / 2.0f, 0.0f));
    this->addChild(colorButtonLayout);
    
    
    ui::Button* backButton=ui::Button::create();
    backButton->setAnchorPoint(Vec2(0.0, 1.0f));
    backButton->setPosition(Vec2(0.0f, visibleSize.height));
    backButton->loadTextures("backButton.png", "backButtonPressed.png");
    backButton->addTouchEventListener(CC_CALLBACK_2(DrawingCanvas::backPressed,this));
    this->addChild(backButton);
    
    
    ui::Button* clearButton=ui::Button::create();
    clearButton->setAnchorPoint(Vec2(1.0f, 1.0f));
    clearButton->setPosition(Vec2(visibleSize.width, visibleSize.height));
    clearButton->loadTextures("clearButton.png", "clearButtonPressed.png");
    clearButton->addTouchEventListener(CC_CALLBACK_2(DrawingCanvas::ClearPressed,this));
    this->addChild(clearButton);
    
    
    for (int i = 1; i <= 5; ++i)
    {
        ui::Button* colorButton = ui::Button::create();
        colorButton->setAnchorPoint(Vec2(0.5f, 0.0f));
        colorButton->setPosition(Vec2(visibleSize.width * i * (1.0f/6.0f), 0.0f));
        colorButton->loadTextures("colorSwatch.png", "colorSwatch.png");
        colorButton->addTouchEventListener(CC_CALLBACK_2(DrawingCanvas::colorChangePressed, this));
        colorButton->setColor(Color3B(COLOR_BLUE));
        colorButtonLayout->addChild(colorButton);
    }
    
   // pauseNodeAndDescendants(colorButtonLayout);
   
    
    Vector<Node*> child;
    child=colorButtonLayout->getChildren();
    child.at(0)->setColor(Color3B(COLOR_RED));
    child.at(1)->setColor(Color3B(COLOR_YELLOW));
    child.at(2)->setColor(Color3B(COLOR_BLUE));
    child.at(3)->setColor(Color3B(COLOR_GREEN));
    child.at(4)->setColor(Color3B(COLOR_PURPLE));

    
    check = Sprite::create("checkMark.png");
    check->setAnchorPoint(Vec2(0.5f, 0.5f));
    check->setNormalizedPosition(Vec2(0.5f, 0.5f));
    
    child.at(3)->addChild(check);
    

    
    
}


void DrawingCanvas::backPressed(cocos2d::Ref *pSender, ui::Widget::TouchEventType eEventType)
{
    
    SceneManager::getInstance()->returnToLobby();
    
}



void DrawingCanvas::ClearPressed(cocos2d::Ref *pSender, ui::Widget::TouchEventType eEventType)
{
    
    drawNode->clear();
    
}

void DrawingCanvas::colorChangePressed(cocos2d::Ref *pSender, ui::Widget::TouchEventType eEventType)
{
    
   
    
    ui::Button* pressedButton = static_cast<ui::Button*>(pSender);
    Touch* touch=static_cast<Touch*> (pSender);
    Vec2 pos=drawNode->convertTouchToNodeSpace(touch);
    
    selecetedColor =(Color4F)pressedButton->getColor();
    check->retain();
    check->removeFromParent();
    pressedButton->addChild(check);
    
    
    if (eEventType == ui::Widget::TouchEventType::BEGAN)
    {
        pressedButton->setScale(0.85);
        
    }
    
    if (eEventType == ui::Widget::TouchEventType::MOVED)
    {
        pressedButton->setScale(1);
        
    }
    if (eEventType == ui::Widget::TouchEventType::ENDED) //FUCK YEAH
        
    {
        pressedButton->setScale(1);
        
    }
    
    
    
    
    
    
    
    
    
  
}


void DrawingCanvas::pauseNodeAndDescendants(Node *pNode)
{

    
    for(const auto &child : pNode->getChildren())
    {
        //this->pauseNodeAndDescendants(child);
        child->setColor(Color3B(COLOR_YELLOW));
        
    }
}



void DrawingCanvas::setNetworkedSession(bool networked)
{
    networkedSession=networked;
    
}


void DrawingCanvas::setter()
{
    
    
}


void DrawingCanvas::getter()
{
    
    
}



void DrawingCanvas::receivedData(const void *data, unsigned long length)
{
    
    const char* cstr = reinterpret_cast<const char*>(data);
    std::string json = std::string(cstr, length);
    JSONPacker::LineData lineData = JSONPacker::unpackLineDataJSON(json);
    drawNode->drawSegment(lineData.startPoint, lineData.endPoint, lineData.radius, lineData.color);
}


void DrawingCanvas::sendStrokeOverNetwork(cocos2d::Vec2 startPoint, cocos2d::Vec2 endPoint, float radius, cocos2d::Color4F color)
{
    JSONPacker::LineData lineData;
    lineData.startPoint = startPoint;
    lineData.endPoint = endPoint;
    lineData.radius = radius;
    lineData.color = color;
    
    std::string json = JSONPacker::packLineData(lineData);
    
    SceneManager::getInstance()->sendData(json.c_str(), json.length());

    
}







