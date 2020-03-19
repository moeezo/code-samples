//
//  MenuMap.hpp
//  CandyCreatures
//
//  Created by moeezo saleem on 12/21/15.
//
//

#ifndef MenuMap_hpp
#define MenuMap_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
#include "CRHud.h"
#include "TutorialScreen.h"
#include "CRSingleton.h"

USING_NS_CC;

class MenuMap : public Scene, CRHudDelegate, TutorialScreenDelegate {
private:
    EventListenerTouchOneByOne* touchListener;
    Sprite* bgSprite;
    cocos2d::ui::Button *Level1Button;
    cocos2d::ui::Button *Level2Button;
    
    Vec2 initialTouch;
    Vec2 finalTouch;
    bool hasDragged;
    void dragBackgroundDown();
    void dragBackgroundUp();
    
    void moveBackground();
    void setUpLevelButtons();
    void level1ButtonClicked();
    void level2ButtonClicked();
    bool checkLockStatus(int levelId);
    Label* getLabelWithId(int levelId, Color4B color, float lsize);
    Rect scaleRectangle( Rect rec, float scaleX, float scaleY);
    Vec2 getRandomPos();
    
public:
    
    CRHud * CRhud;
    void addCRHud();
    TutorialScreen * tutorialScreen;
    void addTutorialScreen();
    void tutorialScreenStartButtonSelected();
    void tutorialScreenHomeButtonSelected();
   
    
    static MenuMap *create();
    virtual bool init();
    
    bool onTouchBegan(Touch *touch, Event *unused_event);
    void onTouchMoved (Touch *touch, Event *unused_event);
    void onTouchEnded(Touch *touch, Event *unused_event);
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    void update(float dt);
    
    // a selector callback
    //void menuCloseCallback(cocos2d::Ref* pSender);
    
    
};



#endif /* MenuMap_hpp */
