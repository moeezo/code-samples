//
//  CandyMonster.cpp
//  CandyCreatures
//
//  Created by moeezo saleem on 12/17/15.
//
//

#include "CandyMonster.h"

#define UP_N_DOWN_MOVE 701
#define FORWARD_MOVE 702

CandyMonster * CandyMonster::create()
{
    CandyMonster *view = new CandyMonster();
    
    if (view && view->initWithFile("Monster_ingame.png")){
        
        view->setAnchorPoint(Vec2(0.5, 0.5));
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



void CandyMonster::initialize()
{
    
    this->speedVerticle = 50;
    this->speedHorizontal = 10;
    this->prevSpeedHorizontal = 10;
    this->collisionOffset = 10;
    this->collisionOffsetYtop= Director::getInstance()->getVisibleSize().height * 0.2;
    this->collisionOffsetYbottom = Director::getInstance()->getVisibleSize().height * 0.14;
    this->moveByActionDuration = 0.1; //was 0.2
    this->isHit = false;
    this->hitCount = 0;
    this->hasWon = false;
    this->isOutside = false;
    this->timeOutside = 0;
    this->shouldWalkStraight = false;
    this->shouldCatchPlayer = false;
    this->upAndDownMotion();
    this->forwardMotion();
    this->scheduleUpdate();
    
    
}

void CandyMonster::update(float dt)
{
    if(isOutside == true){
        timeOutside = timeOutside+1;
        if(timeOutside > 20){
            this->hasWon = true;
        }
    }
    else{
        this->timeOutside = 0;
    }
    
    if(this->shouldWalkStraight == true)
    {
        this->shouldCatchPlayer = true;
    }
}

void CandyMonster::onExit()
{
    //this->delegate = nullptr;
    
    this->Sprite::onExit();
}

void CandyMonster::upAndDownMotion()
{
    if(this->shouldWalkStraight == false)
    {
        CallFunc *checkTop = CallFunc::create(CC_CALLBACK_0(CandyMonster::checkTopWall, this));
        CallFunc *checkBottom = CallFunc::create(CC_CALLBACK_0(CandyMonster::checkBottomWall, this));
        
        auto moveByAction = MoveBy::create(this->moveByActionDuration, Vec2(0 , this->speedVerticle));
        
        CallFunc *repeat = CallFunc::create([ this ]()
                                            {
                                                this->upAndDownMotion();
                                                
                                            });
        
        auto repeatActionSeq = Sequence::create( checkTop, checkBottom, moveByAction, repeat, NULL);
        repeatActionSeq->setTag(UP_N_DOWN_MOVE);
        this->runAction(repeatActionSeq);
    }
}


void CandyMonster::forwardMotion(){
    
    
    if (shouldWalkStraight == false)
    {
        if(isHit==true){
            this->setDisplayFrame(SpriteFrame::create("Monster_hit_state.png", Rect(0,0,311,343)));
            this->hitAnimation();
            this->speedHorizontal = this->prevSpeedHorizontal * -0.8;
            
            float delayForRestore= this->hitCount * 0.5;
            this->scheduleOnce(schedule_selector(CandyMonster::restoreSpeedHorizontal), delayForRestore);
            
        }
        else
        {
            this->setDisplayFrame(SpriteFrame::create("Monster_ingame.png", Rect(0,0,311,343)));
            this->speedHorizontal = this->prevSpeedHorizontal;
        }
        
        CallFunc *checkLeft = CallFunc::create(CC_CALLBACK_0(CandyMonster::checkLeftWall, this));
        
        auto moveByAction = MoveBy::create(this->moveByActionDuration, Vec2(this->speedHorizontal, 0));
        
        CallFunc *repeat = CallFunc::create([ this ]()
                                            {
                                                this->forwardMotion();
                                            });
        
        auto repeatActionSeq = Sequence::create( checkLeft, moveByAction, repeat, NULL);
        repeatActionSeq->setTag(FORWARD_MOVE);
        this->runAction(repeatActionSeq);
    }
}

void CandyMonster::hitAnimation()
{
    this->setPosition(Vec2(this->getPositionX(), this->getPositionY()+ 20));
    this->setPosition(Vec2(this->getPositionX(), this->getPositionY() - 20));
}

void CandyMonster::checkRightWall(){
    auto containerSize = Director::getInstance()->getVisibleSize();
    auto containerOrigin = Director::getInstance()->getVisibleOrigin();
    
    Rect monsterRect = this->getBoundingBox();
    float monX = monsterRect.getMaxX();
    float offsetX= this->speedVerticle;
    monX= monX+offsetX;
    float maxScreenX= containerOrigin.x + containerSize.width + this->collisionOffset;
    if(monX > maxScreenX ){
        //do something if monster goes out of the screen
       // this->speedHorizontal = this->speedHorizontal * -1;
       
    }
}

void CandyMonster::checkLeftWall(){
    auto containerOrigin = Director::getInstance()->getVisibleOrigin();
    
    Rect monsterRect = this->getBoundingBox();
    float monX = monsterRect.getMidX();
    float offsetX= this->speedVerticle;
    monX= monX+offsetX;
    float minScreenX= containerOrigin.x - this->collisionOffset;
    if(monX < minScreenX ){
        isOutside = true;
        CCLOG("Zombie collided with the left wall");
    }
    else
    {
        isOutside= false;
    }
}

void CandyMonster::checkTopWall(){
    auto containerSize = Director::getInstance()->getVisibleSize();
    auto containerOrigin = Director::getInstance()->getVisibleOrigin();
    Rect monRect = this->getBoundingBox();
    float monY = monRect.getMaxY();
    float offsetY= this->speedVerticle;
    monY = monY + offsetY;
    float maxScreenY= containerOrigin.y + containerSize.height - this->collisionOffsetYtop;
    if(monY > maxScreenY ){
        this->speedVerticle = this->speedVerticle * -1;
        CCLOG("Zombie collided with the top wall");
    }
}

void CandyMonster::checkBottomWall(){
   
    auto containerOrigin = Director::getInstance()->getVisibleOrigin();
    Rect monRect = this->getBoundingBox();
    float monY = monRect.getMinY();
    float offsetY= this->speedVerticle;
    monY = monY + offsetY;
    float minScreenY= containerOrigin.y + this->collisionOffsetYbottom;
    if(monY < minScreenY ){
        this->speedVerticle = this->speedVerticle * -1;
        CCLOG("Zombie collided with the bottom wall");
    }
}

void CandyMonster::restoreSpeedHorizontal(float dt){
        this->isHit=false;
    CCLOG("the speed has been restored!");
}
