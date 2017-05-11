//
//  Lobby.hpp
//  doodler
//
//  Created by mac on 2016-09-05.
//
//

#ifndef Lobby_hpp
#define Lobby_hpp

#include "cocos2d.h"
#include "cocosGUI.h"
using namespace cocos2d;

class Lobby: public Node
{
    
public:
    CREATE_FUNC(Lobby);
    
protected:
    LayerColor* backGround;
    
    bool init()override;
    void onEnter()override;
    
    void setupUI();
    
    void soloPressed(Ref *pSender,ui::Widget::TouchEventType eEventType);
    void multiPressed(Ref *pSender, ui::Widget::TouchEventType eEventType);
    
    
    
    
    
    
};




























#endif /* Lobby_hpp */
