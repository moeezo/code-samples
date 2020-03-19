//
//  LoseScreen.cpp
//  CandyCreatures
//
//  Created by moeezo saleem on 12/21/15.
//
//

#include "LoseScreen.h"

//Implement Delegate Methods empty
void LoseScreenDelegate::loseScreenHomeButtonSelected()
{
    //Implement in delegate
}

void LoseScreenDelegate::loseScreenRestartButtonSelected()
{
    //Implement in delegate
}


LoseScreen *LoseScreen::getInstance(LoseScreenDelegate *delegate)
{
    static LoseScreen *instance = nullptr;
    
    if (instance == nullptr)
    {
        instance = LoseScreen::create();
        instance->retain();
    }
    
    instance->delegate = delegate;
    
    return instance;
    
}

void LoseScreen::setDelegate(LoseScreenDelegate *delegate)
{
    this->delegate = delegate;
}

LoseScreen * LoseScreen::create()
{
    LoseScreen *screen = new LoseScreen();
    
    if (screen && screen->initWithFile("Play_screen_overlay.png"))
    {
        screen->setAnchorPoint(Vec2(0, 0));
        
        auto screenSize = Director::getInstance()->getVisibleSize();
        CCLOG("Visible size %f , %f", screenSize.width, screenSize.height);
        auto screenOrigin = Director::getInstance()->getVisibleOrigin();
        screen->setPosition(screenOrigin);
        screen->setScaleY(screenSize.height/screen->getContentSize().height);
        screen->setScaleX(screenSize.width/screen->getContentSize().width);   
        screen->initialize();
        screen->autorelease();
        
        return screen;
    }
    else
    {
        CC_SAFE_DELETE(screen);
        return nullptr;
    }
}

void LoseScreen::onExit()
{
    this->delegate = nullptr;
    
    this->Sprite::onExit();
}

void LoseScreen::initialize()
{
    
    
    this->addMenuButtons();
    
}


void LoseScreen::addMenuButtons()
{
    
    Size containerSize = this->getContentSize();
    auto containerOrigin = this->getBoundingBox().origin;
    
    this->background = Sprite::create("Play_screen_bg.png");
    this->background->setAnchorPoint(Vec2(0.5,0.5));
    this->background->setScaleX(this->background->getScaleX() * 1.6);
    this->background->setScaleY(this->background->getScaleY()*1.4);
    float bkX = containerOrigin.x + containerSize.width*0.5;
    float bkY= containerOrigin.y + containerSize.height*0.5;
    this->background->setPosition(Vec2(bkX, bkY));
    this->addChild(this->background);
    
    float buttonHeight = containerSize.height * 0.12;
    float buttonWidth = containerSize.width * 0.08;  
    
    this->loseText = Label::createWithTTF("You Lost the Level!", "GROBOLD.ttf", buttonHeight*0.4);
    this->loseText->setPosition(this->background->getBoundingBox().origin + this->background->getBoundingBox().size* 0.5);
    this->addChild(this->loseText);
    
   
    
    float x = this->background->getBoundingBox().origin.x + this->background->getBoundingBox().size.width*0.5;   
    
    float y = containerOrigin.y + containerSize.height * 0.25;  //+50
    

    
    auto button1 = cocos2d::ui::Button::create("Game_Over_PlayAgain_unpressed.png", "Game_Over_PlayAgain_pressed.png", "Game_Over_PlayAgain_pressed.png");
    
    button1->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                this->delegate->loseScreenRestartButtonSelected();
                CCLOG("Button1 clicked!");
                break;
            default:
                break;
        }
    });
    
    button1->setPosition(Vec2(x,y));
    button1->setScaleX(buttonWidth / button1->getContentSize().width);
    button1->setScaleY(buttonHeight / button1->getContentSize().height);
    this->btnRestart = button1;
    this->addChild(this->btnRestart);
    
    //////set up the main menu button at the top left
    x = this->background->getBoundingBox().origin.x + this->background->getBoundingBox().size.width * 0.88;
    y = this->background->getBoundingBox().origin.y + this->background->getBoundingBox().size.height * 0.88;
    
    auto button3 = cocos2d::ui::Button::create("Play_screen_cross_unpressed.png", "Play_screen_cross_pressed.png", "Play_screen_cross_pressed.png");
    
    button3->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                this->delegate->loseScreenHomeButtonSelected();
                CCLOG("Button3 clicked!");
                break;
            default:
                break;
        }
    });
    
    button3->setPosition(Vec2(x,y));
    button3->setScaleX(buttonWidth / button3->getContentSize().width);
    button3->setScaleY(buttonHeight / button3->getContentSize().height);
    this->btnHome = button3;
    this->addChild(this->btnHome);
}

void LoseScreen::show()
{
    this->setVisible(true);
    
}

void LoseScreen::hide()
{
    this->setVisible(false);
    
}

void LoseScreen::updateScreenWithInfo(int levelId, float bestPossibleTime)
{
    this->bestTime = bestPossibleTime;
    
    this->levelId = levelId;
    
}


