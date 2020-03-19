//
//  TutorialScreen.cpp
//  CandyCreatures
//
//  Created by moeezo saleem on 12/21/15.
//
//

#define BTN_ZINDEX  50
#define TUTORIALSCREEN_ZINDEX 0

#include "TutorialScreen.h"

//Implement Delegate Methods empty
void TutorialScreenDelegate::tutorialScreenHomeButtonSelected()
{
    //Implement in delegate
}

void TutorialScreenDelegate::tutorialScreenStartButtonSelected()
{
    //Implement in delegate
}


TutorialScreen *TutorialScreen::getInstance(TutorialScreenDelegate *delegate)
{
    static TutorialScreen *instance = nullptr;
    
    if (instance == nullptr)
    {
        instance = TutorialScreen::create();
        instance->retain();
    }
    
    instance->delegate = delegate;
    
    return instance;
    
}

void TutorialScreen::setDelegate(TutorialScreenDelegate *delegate)
{
    this->delegate = delegate;
}

TutorialScreen * TutorialScreen::create()
{
    TutorialScreen *screen = new TutorialScreen();
    
    if (screen && screen->initWithFile("Play_screen_overlay.png"))
    {
        screen->setAnchorPoint(Vec2(0, 0));
        
        auto screenSize = Director::getInstance()->getVisibleSize();
        auto screenOrigin = Director::getInstance()->getVisibleOrigin();
        screen->setPosition(screenOrigin);
        screen->setScaleY(screenSize.height/screen->getContentSize().height);
        screen->setScaleX(screenSize.width/screen->getContentSize().width);
        
        // screen->setContentSize(SIZE_SCREEN);
    
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

void TutorialScreen::onExit()
{
    this->delegate = nullptr;
    
    this->Sprite::onExit();
}

void TutorialScreen::initialize()
{
    
    this->addMenuButtons();
    
}


void TutorialScreen::addMenuButtons()
{
    
    Size containerSize = this->getContentSize();
    auto containerOrigin= this->getBoundingBox().origin;
    CCLOG("The origin for loseScreen is %f, %f", containerOrigin.x, containerOrigin.y);

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
    
    Label * gtitle = Label::createWithTTF("LEVEL 1", "GROBOLD.ttf", buttonHeight*0.65);
    gtitle->setPosition(this->background->getBoundingBox().origin.x + this->background->getBoundingBox().size.width* 0.5, this->background->getBoundingBox().origin.y + this->background->getBoundingBox().size.height* 0.75);
    this->addChild(gtitle);

    
    this->tutText = Label::createWithTTF("Tap to aim and shoot at the Creature", "GROBOLD.ttf", buttonHeight*0.4);
    this->tutText->setPosition(this->background->getBoundingBox().origin + this->background->getBoundingBox().size* 0.5);
    this->addChild(this->tutText);
	
    float x = containerOrigin.x + (containerSize.width*0.5);//0.575; 
    float y = containerOrigin.y + (containerSize.height * 0.3);//50.0;
    
    auto button1 = cocos2d::ui::Button::create("Play_screen_PLAY_unpressed.png", "Play_screen_PLAY_pressed.png", "Play_screen_PLAY_pressed.png");
    
    button1->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                this->delegate->tutorialScreenStartButtonSelected();
                CCLOG("Button1 clicked!");
                break;
            default:
                break;
        }
    });
    
    
    button1->setPosition(Vec2(x,y));
    button1->setScaleX((buttonWidth*2)/button1->getContentSize().width);
    button1->setScaleY((buttonHeight*2)/button1->getContentSize().height);
    this->btnStart = button1;
    this->addChild(this->btnStart, BTN_ZINDEX);
    
    auto buttonWidth1 =button1->getBoundingBox().size.width;
    x = x+ 20+ buttonWidth1;
    
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
                this->delegate->tutorialScreenHomeButtonSelected();
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
    this->addChild(this->btnHome, BTN_ZINDEX);
    
    
}

void TutorialScreen::show()
{
    this->setVisible(true);
    
}

void TutorialScreen::hide()
{
    this->setVisible(false);
    
}

void TutorialScreen::addTutorialWithName(std::string name)
{
    this->tutorialSprite = Sprite::create(name);
    this->tutorialSprite->setAnchorPoint(Vec2(0,0));
    auto winOrigin = Director::getInstance()->getVisibleOrigin();
    auto winSize = Director::getInstance()->getVisibleSize();
    this->tutorialSprite->setScaleX(winSize.width / this->tutorialSprite->getContentSize().width);
    this->tutorialSprite->setScaleY(winSize.height / this->tutorialSprite->getContentSize().height);
    this->setPosition(winOrigin);
    this->addChild(this->tutorialSprite, TUTORIALSCREEN_ZINDEX);
}
