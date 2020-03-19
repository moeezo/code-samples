//
//  CRHud.cpp
//  CandyCreatures
//
//  Created by moeezo saleem on 12/19/15.
//
//

#include "CRHud.h"
#include "CRSingleton.h"

void CRHudDelegate::CRHudPauseButtonSelected()
{
    //Implement in delegate
}


CRHud * CRHud::getInstance(CRHudDelegate *delegate)
{
    static CRHud *instance = nullptr;
    
    if (instance == nullptr)
    {
        instance = CRHud::create();
        instance->retain();
    }
    instance->delegate = delegate;
    
    return instance;
}


void CRHud::setDelegate(CRHudDelegate *delegate)
{
    this->delegate = delegate;
}

CRHud * CRHud::create()
{
    CRHud *view = new CRHud();
    
    if (view && view->init())  //GreyLoadingBar
    {
        view->setAnchorPoint(Vec2(0, 0));
        
       
        
        view->overlayBar = Sprite::create("MapScreen_HUD_overlay.png");
        view->setContentSize(view->overlayBar->getContentSize());
        auto containerSize = Director::getInstance()->getVisibleSize();
        auto containerOrigin = Director::getInstance()->getVisibleOrigin();
        
        view->setScaleY( containerSize.height *0.1/ view->getContentSize().height);
        view->setScaleX(containerSize.width/ view->getContentSize().width);
        view->setPosition(Vec2(0, containerOrigin.y + containerSize.height *0.9));
       // view->setPosition(Vec2(0, containerSize.height - (height * 1.05)));
        //view->setContentSize(Size(containerSize.width, (height)));
        
        view->initialize();
        
        view->autorelease();
        
        return view;
    }
    else
    {
        CC_SAFE_DELETE(view);
        return nullptr;
    }
}
void CRHud::onExit()
{
    this->delegate = nullptr;
    
    this->Sprite::onExit();
}

void CRHud::initialize()
{
    //Size containerSize = this->getBoundingBox().size;
    Size containerSize = this->getContentSize();
    auto containerOrigin = this->getBoundingBox().origin;
    
    this->overlayBar->setAnchorPoint(Vec2(0,0));
    this->addChild(this->overlayBar);
    //auto labelW = containerSize.width * 0.3;
    auto labelH = containerSize.height * 0.35;
    this->labelHeight = labelH;

    
    this->paddingH = containerSize.width *0.01;
    this->paddingV = containerSize.height *0.45;
    
    float x = this->paddingH;
    float y = this->paddingV;
    
    CRLevelData* currLevel = CRSingleton::getInstance()->getCurrentLevelData();
    int levelId = currLevel->getLevelId();
    std::string titleString = StringUtils::format("Level: %d", (levelId+1));
    this->lblTitle = Label::createWithTTF(titleString, "GROBOLD.ttf", labelH); //labelHeight * 0.70
    this->lblTitle->setColor(Color3B(249,224,148));
    this->lblTitle->setAnchorPoint(Vec2(0,0));
    this->lblTitle->setPosition(Vec2(x,y));
    this->addChild(this->lblTitle);
    
    x = x+ containerSize.width * 0.35;
    string time = getTimeString(0);
    this->lblTimer = Label::createWithTTF(time, "GROBOLD.ttf", labelH); //labelHeight * 0.70
    this->lblTimer->setAnchorPoint(Vec2(0,0));
    this->lblTimer->setColor(Color3B(249,224,148));
   // this->lblTimer->setWidth(labelW/ this->lblTimer->getContentSize().width);
   // this->lblTimer->setHeight(labelH/this->lblTimer->getContentSize().height);
    this->lblTimer->setPosition(Vec2(x, y));
    this->addChild(this->lblTimer);
    
    
    x += containerSize.width*0.5;  //0.85
    y = containerSize.height *0.3;
    this->viwAllLives = Sprite::create("MapScreen_02.png");
    this->viwAllLives->setAnchorPoint(Vec2(0,0));
    this->viwAllLives->setScaleX(containerSize.width*0.07/this->viwAllLives->getContentSize().width);  //width*0.12
    this->viwAllLives->setScaleY(containerSize.height*0.7/this->viwAllLives->getContentSize().height);  //height* 0.8
    this->viwAllLives->setPosition(x,y);
    this->addChild(this->viwAllLives);
   
    this->refreshNumberOfLives();
    this->setupTimerView();
    
}

void CRHud::refreshNumberOfLives(){
    int remainingLives = CRSingleton::getLivesCount();
    CCLOG("Remaining lives: %d", remainingLives);
    string lifeText = StringUtils::format("0%d", remainingLives);
    auto myLabel = Label::createWithTTF(lifeText, "GROBOLD.ttf", this->labelHeight*0.75 );
    myLabel->setColor(Color3B(249,224,148));
    //auto myLabel = Label::createWithTTF(lifeText, "Marker Felt.ttf", 11);
    auto containerSize = this->getContentSize();
    auto containerOrigin = this->getBoundingBox().origin;
    myLabel->setAnchorPoint(Vec2(0.5,0.5));
    myLabel->setPosition(Vec2(containerSize.width *0.86 + this->viwAllLives->getBoundingBox().size.width*0.5, containerSize.height * 0.3 + this->viwAllLives->getBoundingBox().size.height*0.4));
    this->livesCountLabel = myLabel;
    this->addChild(this->livesCountLabel);

}

string CRHud::getTimeString(int seconds){
    int minutes = seconds / 60;
    int hours = minutes / 60;
    
    int remainingSeconds = seconds % 60;
    
    string hourString = (hours > 9) ? to_string(hours) : "0" + to_string(hours);
    string minuteString = (minutes > 9) ? to_string(minutes) : "0" + to_string(minutes);
    string secondString = (remainingSeconds > 9) ? to_string(remainingSeconds) : "0" + to_string(remainingSeconds);
    
    return hourString + " : " + minuteString + " : " + secondString;

}

string CRHud::getTimeStringFromMilliSeconds(float milliSeconds)
{
    int minutes = (int) (milliSeconds / 60);
    int remainingSeconds = (int) (milliSeconds) % 60;
    float tenthSecond = (milliSeconds - (float)remainingSeconds - (float)(minutes*60)) * 100 ;
    int mTenthSecond = (int)tenthSecond % 60;
    
    string minuteString = (minutes > 9) ? to_string(minutes) : "0" + to_string(minutes);
    string secondString = (remainingSeconds  > 9) ? to_string(remainingSeconds) : "0" + to_string(remainingSeconds);
    string milli = (mTenthSecond > 9) ? to_string(mTenthSecond) : "0" + to_string(mTenthSecond);
    return minuteString + " : " + secondString + " : " + milli;
}

void CRHud::setupTimerView()
{
   
}

void CRHud::resetHud()
{
    this->refreshNumberOfLives();
    this->resetTimer();
   
}

void CRHud::update(float dt)
{
    updateTimer(dt);
}

void CRHud::updateTimer(float dt)
{
    numSeconds = numSeconds + dt;
    this->lblTimer->setString(this->getTimeStringFromMilliSeconds(numSeconds));
   // CCLOG("the string time has been set! %f", numSeconds);
}

void CRHud::resetTimer()
{
    this->numSeconds = 0;
    this->updateTimer(0);
    this->unscheduleUpdate();
}

void CRHud::startTime()
{
    this->scheduleUpdate();
    
}

void CRHud::stopTime()
{
    this->unscheduleUpdate();
}

void CRHud::resumeTime()
{
    
    this->scheduleUpdate();
}

void CRHud::pauseTime()
{
    
    this->unscheduleUpdate();
}

void CRHud::hideOverlay()
{
    this->overlayBar->setVisible(false);
}

