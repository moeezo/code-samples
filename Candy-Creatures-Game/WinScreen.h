//
//  WinScreen.hpp
//  CandyCreatures
//
//  Created by moeezo saleem on 12/20/15.
//
//

#ifndef WinScreen_hpp
#define WinScreen_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;


class WinScreenDelegate
{
public:
    
    virtual void WinScreenNextLevelButtonSelected();
    virtual void WinScreenRestartButtonSelected();
    virtual void WinScreenHomeButtonSelected();
    
};

class WinScreen : public Sprite
{
private:
    
    cocos2d::ui::Button *btnHome;
    cocos2d::ui::Button *btnRestart;
    cocos2d::ui::Button *btnNextLevel;
    Label * winText;
    
    Sprite * background;
    float bestTime;
    
    int levelId;
  
    
    WinScreenDelegate *delegate;
    
    static WinScreen * create();
    
    void addMenuButtons();
    
    virtual void initialize();
    virtual void onExit();
    
    
public:
    
    static WinScreen * getInstance(WinScreenDelegate *delegate);
    
    void setDelegate(WinScreenDelegate *delegate);
    
   
    void updateScreenWithInfo(int levelId, float bestPossibleTime);
    
    virtual void show();
    virtual void hide();
};



#endif /* WinScreen_hpp */
