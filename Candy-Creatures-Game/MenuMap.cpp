//
//  MenuMap.cpp
//  CandyCreatures
//
//  Created by moeezo saleem on 12/21/15.
//
//

#include "MenuMap.h"
#include "Level1.h"

MenuMap* MenuMap::create() {
    MenuMap *pRet = new MenuMap();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return nullptr;
    }
}

void MenuMap::addCRHud(){
    this->CRhud = CRHud::getInstance(this);
    this->addChild(this->CRhud, 100);
    this->CRhud->setDelegate(this);
}

void MenuMap::addTutorialScreen(){
    
    if(this->tutorialScreen !=nullptr)
    {
        this->tutorialScreen->show();
    }
    else
    {
    this->tutorialScreen = TutorialScreen::getInstance(this);
    this->addChild(this->tutorialScreen, 101);
    this->tutorialScreen->setDelegate(this); 
    this->tutorialScreen->show();
    }
}


void MenuMap::tutorialScreenStartButtonSelected(){
    CCLOG("The button restart for the tutorial screen has been clicked and this is the result");
    auto scene = Level1::create();
    Director::getInstance()->replaceScene(scene);
    

}



void MenuMap::tutorialScreenHomeButtonSelected(){
    CCLOG("The home button for the tutorial screen has been clicked and this is the result");
    this->tutorialScreen->hide();
}


bool MenuMap::init()
{
    //initialize the super first
    if ( !Scene::init() )
    {
        return false;
    }
    
    this->touchListener = EventListenerTouchOneByOne::create();
    this->touchListener->setSwallowTouches(true);
    this->touchListener->onTouchBegan = CC_CALLBACK_2(MenuMap::onTouchBegan, this);
    this->touchListener->onTouchMoved = CC_CALLBACK_2(MenuMap::onTouchMoved, this);
    this->touchListener->onTouchEnded = CC_CALLBACK_2(MenuMap::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    auto containerSize = Director::getInstance()->getVisibleSize();
    auto containerOrigin = Director::getInstance()->getVisibleOrigin();
    
  
    //initialize the bgSprite
    Sprite* bkgrd = Sprite::create("MapScreen_01.png");
    bkgrd->setAnchorPoint(Vec2(0,0));
    float bkScaleX= containerSize.width/bkgrd->getContentSize().width;
    bkgrd->setScaleX(bkScaleX);
    bkgrd->setScaleY(containerSize.height *1.2/bkgrd->getContentSize().height);
    bkgrd->setPosition(containerOrigin);
    this->bgSprite = bkgrd;
    this->addChild(this->bgSprite); 
    this->setUpLevelButtons();
    srand((unsigned int)time(nullptr));
    this->scheduleUpdate();
  
    return true;
    
}

void MenuMap::setUpLevelButtons()
{
    auto button1 = cocos2d::ui::Button::create("MapScreen_lvl01.png", "MapScreen_lvl01.png", "MapScreen_lvl01.png");
    
    button1->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                this->level1ButtonClicked();
                CCLOG("Button for level 1 in menu map clicked!");
                break;
            default:
                break;
        }
    });
    
    this->Level1Button = button1;
    this->Level1Button->setAnchorPoint(Vec2(0.5,0.5));
    this->bgSprite->addChild(this->Level1Button);
    auto containerSize = this->bgSprite->getContentSize();
    auto containerOrigin = this->bgSprite->getBoundingBox().origin;
    float posX = containerOrigin.x +  this->Level1Button->getBoundingBox().size.width * 0.5 + containerSize.width * 0.42;
    float posY = containerOrigin.y + this->Level1Button->getBoundingBox().size.height * 0.5 + containerSize.height * 0.2;
    this->Level1Button->setPosition(Vec2(posX, posY));
    
    //////////add second level button
    auto button2 = cocos2d::ui::Button::create("MapScreen_lvl_bg.png", "MapScreen_lvl_bg.png", "MapScreen_lvl_bg.png");
    
    button2->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                this->level2ButtonClicked();
                CCLOG("Button for level 2 in menu map clicked!");
                break;
            default:
                break;
        }
    });
    
    this->Level2Button = button2;
    this->Level2Button->setAnchorPoint(Vec2(0.5,0.5));
    this->bgSprite->addChild(this->Level2Button);
    float posX2 = containerOrigin.x +  this->Level2Button->getBoundingBox().size.width * 0.5 + containerSize.width * 0.25;
    float posY2 = containerOrigin.y + this->Level2Button->getBoundingBox().size.height * 0.5 + containerSize.height * 0.3;
    this->Level2Button->setPosition(Vec2(posX2, posY2));
    
    ////////set Level 2 title text
    //get lock status of level 2 , rem level 2 has id = 1
    bool islevel2Locked = checkLockStatus(1);
    Color4B levelColor;
    if ( islevel2Locked == true)
    {
        levelColor = Color4B(136, 84, 105, 255);
    }
    else
    {
        levelColor = Color4B(254, 0, 103, 255);
    }
    
    auto labelContainerSize= this->Level2Button->getBoundingBox().size;
    
    float labelSize = labelContainerSize.height *0.44;
    Label *level2Title = this->getLabelWithId(1, levelColor, labelSize);
    level2Title->setAnchorPoint(Vec2(0.5, 0.5));
    float lposX =  labelContainerSize.width*0.5;
    float lposY =  labelContainerSize.height*0.45;
    level2Title->setPosition(lposX, lposY);
    this->Level2Button->addChild(level2Title);

}


Label* MenuMap::getLabelWithId( int levelId, Color4B color, float lsize)
{
    auto mytitle = Label::createWithTTF(StringUtils::format("%d", (levelId+1)), "GROBOLD.ttf", lsize);
    mytitle->setTextColor(color);
    return mytitle;
}

bool MenuMap::checkLockStatus(int levelId)
{
    return CRSingleton::getInstance()->getIsLockedForLevel(levelId);
}

void MenuMap::level1ButtonClicked()
{
     CCLOG("result of clicking level 1 button");
    this->addTutorialScreen();

    
}

void MenuMap::level2ButtonClicked()
{
    CCLOG("result of clicking level 2 button");
}

void MenuMap::moveBackground()
{
    auto containerOrigin = Director::getInstance()->getVisibleOrigin();
    this->bgSprite->setPosition(containerOrigin);
    auto disX= this->bgSprite->getContentSize().width*0.5;//
    //auto movePos = bgPos + Vec2(-disX,0);
    auto moveAction = MoveBy::create(2,Vec2(-disX,0));
    
    CallFunc * again = CallFunc::create([&](){
        this->moveBackground();
    });
    
    auto repeatAction = Sequence::create(  moveAction,again, NULL);
    this->bgSprite->runAction(repeatAction);
}


Vec2 MenuMap::getRandomPos(){
    
    Size containerSize = Director::getInstance()->getVisibleSize();
    auto containerOrigin = Director::getInstance()->getVisibleOrigin();
    
    int containerW= floorf(containerSize.width);
    int containerH= floorf(containerSize.height);
    float randomX= rand() % containerW + 1;
    float randomY= rand() % containerH + 1;
    Vec2 pos= Vec2(randomX, randomY);
    return pos;
}

bool MenuMap::onTouchBegan(Touch * touch, Event * event){
    
    Vec2 touchLocation = touch->getLocation();
    this->initialTouch = touchLocation;
    this->hasDragged = true;
    return true;
}

void MenuMap::onTouchMoved (Touch *touch, Event *unused_event){
    Vec2 touchLocation = touch->getLocation();
    this->finalTouch = touchLocation;
    this->hasDragged = true;
}

void MenuMap::onTouchEnded(Touch *touch, Event *unused_event){
    Vec2 touchLocation= touch->getLocation();
    this->finalTouch = touchLocation;
    this->hasDragged = false;
   
}


void MenuMap::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


void MenuMap::update(float dt)
{
    if (this->initialTouch.y- this->finalTouch.y > 5 && hasDragged == true)
    {
        this->dragBackgroundDown();
    }
    
    if(this->finalTouch.y - this->initialTouch.y > 5 && hasDragged ==  true)
    {
        this->dragBackgroundUp();
    }
  
    
    
}

void MenuMap::dragBackgroundDown()
{
    
    if(  this->bgSprite!= nullptr)
    {
        CCLOG("has entered drag down");
        float topLimit = Director::getInstance()->getVisibleOrigin().y + Director::getInstance()->getVisibleSize().height;
        
        if ((this->bgSprite->getPositionY()+ this->bgSprite->getBoundingBox().size.height) >= topLimit)
       {
            float moveFactor = 20;
            float diffY = this->initialTouch.y - this->finalTouch.y;
            
            this->bgSprite->setPosition( Vec2(this->bgSprite->getPositionX(),this->bgSprite->getPositionY() - (diffY/moveFactor)));
        }
        
    }

}

void MenuMap::dragBackgroundUp()
{
    if(  this->bgSprite!= nullptr)
    {
        CCLOG("has entered drag down");
   
        
        if (this->bgSprite->getPositionY() < 0)
        {
            float moveFactor = 20;
            float diffY = this->finalTouch.y - this->initialTouch.y;
            
            this->bgSprite->setPosition( Vec2(this->bgSprite->getPositionX(),this->bgSprite->getPositionY() + (diffY/moveFactor)));
        }
        
    }
}


Rect MenuMap::scaleRectangle( Rect rec, float scaleX, float scaleY){
    float playerW= rec.size.width * scaleX;
    float playerH= rec.size.height * scaleY;
    float playerX= rec.getMidX() - (playerW * 0.5);
    float playerY= rec.getMidY()- (playerH * 0.5);
    Rect newRect = Rect(playerX, playerY, playerW, playerH);
    return newRect;
}