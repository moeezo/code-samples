//
//  LoseScreen.hpp
//  CandyCreatures
//
//  Created by moeezo saleem on 12/21/15.
//
//

#ifndef LoseScreen_hpp
#define LoseScreen_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;


class LoseScreenDelegate
{
public:
    

    virtual void loseScreenRestartButtonSelected();
    virtual void loseScreenHomeButtonSelected();
    
};

class LoseScreen : public Sprite
{
private:
    
    cocos2d::ui::Button *btnHome;
    cocos2d::ui::Button *btnRestart;
    Sprite * background;
    Label * loseText;
    
    float bestTime;
    
    int levelId;
    
    
    LoseScreenDelegate *delegate;
    
    static LoseScreen * create();
    
    void addMenuButtons();
    
    virtual void initialize();
    virtual void onExit();
    
    
public:
    
    static LoseScreen * getInstance(LoseScreenDelegate *delegate);
    
    void setDelegate(LoseScreenDelegate *delegate);
    
    
    void updateScreenWithInfo(int levelId, float bestPossibleTime);
    
    virtual void show();
    virtual void hide();
};



#endif /* LoseScreen_hpp */
