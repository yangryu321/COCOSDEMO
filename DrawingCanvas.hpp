//
//  DrawingCanvas.hpp
//  doodler
//
//  Created by mac on 2016-09-04.
//
//

#ifndef DrawingCanvas_hpp
#define DrawingCanvas_hpp
#include "cocos2d.h"
#include "cocosGUI.h"
#include "Constants.h"
#include "SceneManager.hpp"

using namespace cocos2d;


class DrawingCanvas: public Node
{
public:
    CREATE_FUNC(DrawingCanvas);
    
protected:
    DrawNode* drawNode;
    LayerColor* backGround;
    
    bool init() override;
    void onEnter() override;
    void setupTouchHandling();
    void setupMenu();
    void backPressed(Ref* pSender,ui::Widget::TouchEventType eEventType);
    void ClearPressed(Ref* pSender, ui::Widget::TouchEventType eEventType);
    void colorChangePressed(Ref* pSender, ui::Widget::TouchEventType eEventType);
    void pauseNodeAndDescendants(Node *pNode);
    bool networkedSession;
    
    // send data
    void sendStrokeOverNetwork(cocos2d::Vec2 startPoint, cocos2d::Vec2 endPoint, float radius, cocos2d::Color4F color);
    
public:
    void setNetworkedSession(bool networked);
    
    Sprite* check;
    Color4F selecetedColor;
    void setter();
    void getter();
    
    //receive data
    void receivedData(const void* data, unsigned long length);
    
    
};






























#endif /* DrawingCanvas_hpp */
