//
//  SceneManager.hpp
//  doodler
//
//  Created by mac on 2016-09-18.
//
//

#ifndef SceneManager_hpp
#define SceneManager_hpp

#include <stdio.h>
#include "NetworkingWrapper.h"
#include "DrawingCanvas.hpp"

class DrawingCanvas;
class SceneManager: public NetworkingDelegate
{
    
    
public:
    static SceneManager* getInstance(); //get a singleton, which is SceneManager here
  
    
    SceneManager();
    ~SceneManager();
    
   // Controll Scences
    void enterSoloGame();
    void returnToLobby();
    
    
    
    
    //
    void sendData(const void *data, unsigned long length);

    void receivedData(const void* data, unsigned long length) override;
    void stateChanged(ConnectionState state) override;
    void connectAndEnterNetworkedGame();
    
    
private:
    
    DrawingCanvas* drawingCanvas;
    void loadDrawingScene(bool networked);
    NetworkingWrapper *netWorkingWrapper; // STEP 1
    
    
};









#endif /* SceneManager_hpp */
