//
//  Level1.hpp
//  CandyCreatures
//
//  Created by moeezo saleem on 12/17/15.
//
//

#ifndef Level1_hpp
#define Level1_hpp

#include "Player.h"
#include "CandyMonster.h"
#include "Level1Background.h"
#include "CRHud.h"
#include "WinScreen.h"
#include "LoseScreen.h"

#include <stdio.h>


USING_NS_CC;

class Level1 : public Scene, CRHudDelegate, WinScreenDelegate, LoseScreenDelegate {
private:
    EventListenerTouchOneByOne* touchListener;
    Player* myPlayer;
    CandyMonster* myMonster;
    Level1Background * myBackground;
    Sprite* bgSprite;
    Sprite* foodToThrow;
    Sprite* timeBar;
    Sprite* tutorialScreen;
    
    float gameDuration;
    float timePassed;
    Vec2 getRandomPos();
    
    void moveBackground();
    void playerEndGameAction();
    void gameOverWinAction();
    
    void throwFood(Vec2 pos);
    void createFood();
    
    void checkFoodCollision();
    void checkPlayerCollision();
    
    Rect scaleRectangle( Rect rec, float scaleX, float scaleY);
    
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
    void resetVariables();
    void resumeAllp();
    
    static Level1 *create();
    virtual bool init();
    void startLevel1(float dt);
    
    bool onTouchBegan(Touch *touch, Event *unused_event);
    void onTouchMoved (Touch *touch, Event *unused_event);
    void onTouchEnded(Touch *touch, Event *unused_event);
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    void update(float dt);
    
    void levelComplete(float dt);
    // a selector callback
    //void menuCloseCallback(cocos2d::Ref* pSender);
    
    
};

#endif /* Level1_hpp */
