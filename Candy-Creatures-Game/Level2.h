//
//  Level2.h
//  Candy Creatures
//
//  Created by moeezo saleem on 12/1/15.
//
//

#ifndef Level2_hpp
#define Level2_hpp

#include "Player2.h"
#include "CRHud.h"
#include "WinScreen.h"
#include "LoseScreen.h"
#include <stdio.h>
#include "FirstObstacle.h"
#include "Level1Background.h"

USING_NS_CC;

class Level2 : public Scene, CRHudDelegate, WinScreenDelegate, LoseScreenDelegate  {
private:
    EventListenerTouchOneByOne* touchListener;
    
    Player2* myPlayer;
    
    Vector<FirstObstacle *> Obstacles;
    Level1Background * myBackground;
    Sprite* timeBar;
    Sprite* tutorialScreen;
    Sprite* levelFinishLine;
    float gameDuration;
    float timePassed;
    Vec2 initialTouch;
    Vec2 finalTouch;
    bool hasDragged;
    bool movePlayerToFinishLine;
    Vec2 getRandomPos();
    Vec2 getRandomPos2();
    void moveBackground();
    void dragPlayer();
    void addObstacle(float dt);
    void addObstacle1(float dt);
    void addObstacle2(float dt);
    void addObstacle3(float dt);
    float heightRandomOffset;
    void movePlayerUp();
    void movePlayerDown();
  
    Rect scaleRectangle( Rect rec, float scaleX, float scaleY);
    void createFinishLine(float dt);
    void checkPlayerCollisionWithObstacle();
    
public:
   
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
    
    static Level2 *create();
    virtual bool init();
    void startLevel2(float dt);
    
    bool onTouchBegan(Touch *touch, Event *unused_event);
    void onTouchMoved (Touch *touch, Event *unused_event);
    void onTouchEnded(Touch *touch, Event *unused_event);
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    void update(float dt);
    
    
    void levelComplete(float dt);
    // a selector callback
    //void menuCloseCallback(cocos2d::Ref* pSender);
    
    
};



#endif /* Level2_hpp */
