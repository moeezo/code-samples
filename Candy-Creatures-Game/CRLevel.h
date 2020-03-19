//
//  CRLevel.hpp
//  CandyCreatures
//
//  Created by moeezo saleem on 12/28/15.
//
//

#ifndef CRLevel_hpp
#define CRLevel_hpp

#include <stdio.h>
#include "CRhud.h"
#include "WinScreen.h"
#include "LoseScreen.h"
#include "TutorialScreen.h"
#include "CRSingleton.h"
#include "CRLevelData.h"
#include "MenuMap.h"

USING_NS_CC;

class CRLevel : public Scene,  CRHudDelegate, WinScreenDelegate, TutorialScreenDelegate, LoseScreenDelegate
{
private:
    
    EventListenerTouchOneByOne *touchListener;
    EventListenerAcceleration *acclerationListener;
    
public:
    
    bool gamePaused;
    
    
    CRHud * CRhud;
    void addCRHud();
    
    WinScreen * winScreen;
    void addWinScreen();
    void WinScreenRestartButtonSelected();
    void WinScreenNextLevelButtonSelected();
    void WinScreenHomeButtonSelected();
    
    LoseScreen * loseScreen;
    void addLoseScreen();
    void loseScreenRestartButtonSelected();
    void loseScreenHomeButtonSelected();
    
    TutorialScreen * tutorialScreen;
    void addTutorialScreen();
    void tutorialScreenStartButtonSelected();
    void tutorialScreenHomeButtonSelected();
    
    int getLevelType();
    float getBestPossibleTime();
    
    /////
    
    
    
    //Touch Listener
    void addTouchListener();
    void removeTouchListener();
    
    //Accelerometer listener
    void addAccelerometerListener();
    void removeAccelerometerListener();
    
    
    virtual void onEnter();
    virtual void onExit();
    
    // **** REQUIRED ****
    //level Life Cycle
    virtual void levelSetup();
    virtual void levelStart();
    virtual void levelResume();
    virtual void levelPause();
    virtual void levelWon();
    virtual void levelLost();
    virtual void levelRestart();
    
    
    //Touch Listener Callback
    virtual bool onTouchBegan(Touch *touch, Event * event);
    virtual void onTouchMoved(Touch *touch, Event * event);
    virtual void onTouchEnded(Touch *touch, Event * event);
    virtual void onTouchCancelled(Touch *touch, Event * event);
    
    //Accelerometer Listener Callback
    virtual void onAcceleration(Acceleration *acc, Event *event);
    
    
    // helper methods
    float randomFloat(float min, float max);
 
    /*!
     Return a Rect computed as the union of the target node's -boundingBox and those of this node's descendant nodes.
     Note that boundingBoxConvertedToNodeSpace() below is automatically called by this method when getting the Rect.
     Computationally intesive if there are many nodes so cache if possible.
     */
    static Rect fullBoundingBox(Node *target);
    /*!
     Return the -boundingBox of another node, converted into this node's local
     coordinate space.
     */
    static Rect boundingBoxConvertedToNodeSpace(Node *target, Node *other);
};

#endif /* CRLevel_hpp */
