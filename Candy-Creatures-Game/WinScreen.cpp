//
//  WinScreen.cpp
//  CandyCreatures
//
//  Created by moeezo saleem on 12/20/15.
//
//

#include "WinScreen.h"

//Implement Delegate Methods empty
void WinScreenDelegate::WinScreenHomeButtonSelected()
{
    //Implement in delegate
}

void WinScreenDelegate::WinScreenRestartButtonSelected()
{
    //Implement in delegate
}

void WinScreenDelegate::WinScreenNextLevelButtonSelected()
{
    //Implement in delegate
}

WinScreen *WinScreen::getInstance(WinScreenDelegate *delegate)
{
    static WinScreen *instance = nullptr;
    
    if (instance == nullptr)
    {
        instance = WinScreen::create();
        instance->retain();
    }
    
    instance->delegate = delegate;
    
    return instance;
    
}

void WinScreen::setDelegate(WinScreenDelegate *delegate)
{
    this->delegate = delegate;
}

WinScreen * WinScreen::create()
{
    WinScreen *screen = new WinScreen();
    
    if (screen && screen->initWithFile("Play_screen_overlay.png"))
    {
        screen->setAnchorPoint(Vec2(0, 0));
        
        auto screenSize = Director::getInstance()->getVisibleSize();
        auto screenOrigin = Director::getInstance()->getVisibleOrigin();
        CCLOG("visible size %f, %f", screenSize.width, screenSize.height);
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

void WinScreen::onExit()
{
    this->delegate = nullptr;
    
    this->Sprite::onExit();
}

void WinScreen::initialize()
{

    
    this->addMenuButtons();
    
}


void WinScreen::addMenuButtons()
{
    
   
    Size containerSize = this->getContentSize();
    auto containerOrigin = this->getBoundingBox().origin;
    
    this->background = Sprite::create("Play_screen_bg.png");
    this->background->setAnchorPoint(Vec2(0.5,0.5));
    this->background->setScaleX(this->background->getScaleX()* 1.6);
    this->background->setScaleY(this->background->getScaleY()*1.4);
    float bkX = containerOrigin.x + containerSize.width*0.5;
    float bkY= containerOrigin.y + containerSize.height*0.5;
    this->background->setPosition(Vec2(bkX, bkY));
    this->addChild(this->background);
   
    float buttonHeight = containerSize.height * 0.12;
    float buttonWidth = containerSize.width * 0.08;  //0.15
    
    this->winText = Label::createWithTTF("You've Won the Level!", "GROBOLD.ttf", buttonHeight*0.4);
    this->winText->setPosition(this->background->getBoundingBox().origin + this->background->getBoundingBox().size* 0.5);
    this->addChild(this->winText);
    
    float paddingH = (this->background->getBoundingBox().size.width - (buttonWidth * 2)) / (3);
    
    float x = this->background->getBoundingBox().origin.x + paddingH;   //+50
    
    float y = containerOrigin.y + containerSize.height * 0.25;  //+50
    
    
    auto button1 = cocos2d::ui::Button::create("Game_Over_PlayAgain_unpressed.png", "Game_Over_PlayAgain_pressed.png", "Game_Over_PlayAgain_pressed.png");
    
    button1->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                this->delegate->WinScreenRestartButtonSelected();
                CCLOG("Button1 clicked!");
                break;
            default:
                break;
        }
    });
    
    button1->setPosition(Vec2(x,y));
    button1->setAnchorPoint(Vec2(0,0.5));
    button1->setScaleX(buttonWidth / button1->getContentSize().width);
    button1->setScaleY(buttonHeight / button1->getContentSize().height);
    this->btnRestart = button1;
    this->addChild(this->btnRestart);
    
    auto buttonWidth1 =button1->getBoundingBox().size.width;
    CCLOG("the button width is %f", buttonWidth1);
    x = x+ paddingH + buttonWidth1;
    
    auto button2 = cocos2d::ui::Button::create("Game_Over_Proceed_unpressed.png", "Game_Over_Proceed_pressed.png", "Game_Over_Proceed_pressed.png");
    
    button2->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                this->delegate->WinScreenNextLevelButtonSelected();
                CCLOG("Button2 clicked!");
                break;
            default:
                break;
        }
    });
    
    button2->setPosition(Vec2(x,y));
    button2->setAnchorPoint(Vec2(0,0.5));
    button2->setScaleX(buttonWidth / button2->getContentSize().width);
    button2->setScaleY(buttonHeight / button2->getContentSize().height);
    this->btnNextLevel = button2;
    this->addChild(this->btnNextLevel);

    //the menu button on the top right of the bkground box
    x = this->background->getBoundingBox().origin.x + this->background->getBoundingBox().size.width * 0.88;
    y = this->background->getBoundingBox().origin.y + this->background->getBoundingBox().size.height * 0.88;
    
    auto button3 = cocos2d::ui::Button::create("Play_screen_cross_unpressed.png", "Play_screen_cross_pressed.png", "Play_screen_cross_pressed.png");
    
    button3->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                this->delegate->WinScreenHomeButtonSelected();
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

void WinScreen::show()
{
    this->setVisible(true);
    
}

void WinScreen::hide()
{
    this->setVisible(false);
    
}

void WinScreen::updateScreenWithInfo(int levelId, float bestPossibleTime)
{
    this->bestTime = bestPossibleTime;
    
    this->levelId = levelId;
   
}




// Touch Delegate


