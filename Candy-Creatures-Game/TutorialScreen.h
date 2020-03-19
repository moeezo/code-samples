//
//  TutorialScreen.hpp
//  CandyCreatures
//
//  Created by moeezo saleem on 12/21/15.
//
//

#ifndef TutorialScreen_hpp
#define TutorialScreen_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;


class TutorialScreenDelegate
{
public:
       
    virtual void tutorialScreenStartButtonSelected();
    virtual void tutorialScreenHomeButtonSelected();  
};

class TutorialScreen : public Sprite
{
private:
    
    cocos2d::ui::Button *btnHome;
    cocos2d::ui::Button *btnStart;
    
    Sprite * tutorialSprite;
    Sprite * background;
    Label * tutText;

    
    int levelId;
    
    
    TutorialScreenDelegate *delegate;
    
    static TutorialScreen * create();
    
    void addMenuButtons();

    
    virtual void initialize();
    virtual void onExit();
    
    
public:
    
    static TutorialScreen * getInstance(TutorialScreenDelegate *delegate);
    
    void setDelegate(TutorialScreenDelegate *delegate);
    
    void addTutorialWithName(std::string name);
    
    virtual void show();
    virtual void hide();
};





#endif /* TutorialScreen_hpp */
