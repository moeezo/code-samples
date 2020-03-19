//
//  FirstObstacle.cpp
//  CandyCreatures
//
//  Created by moeezo saleem on 12/18/15.
//
//

#define FULL_ROTATE 600
#define HALF_ROTATE 601
#define STRAWBERRY_ANIM 602
#define SCALE_ANIM 603

#include "FirstObstacle.h"

FirstObstacle * FirstObstacle::createWithType(int obType)
{
    FirstObstacle *view = new FirstObstacle();
    
    std::string fileName = StringUtils::format("creature%d.png", obType);
    
    if( obType == 7)
    {
        fileName = "StrawberryCreature_1.png";
    }
    
    if (view && view->initWithFile(fileName)){  
        
        view->setAnchorPoint(Vec2(0.5, 0.5));
        view->obstacleType = obType;
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



void FirstObstacle::initialize()
{
    
    
    this->hasMoveEnded =false;
    this->scheduleUpdate();
    if(this->obstacleType == 1 || this->obstacleType == 2 || this->obstacleType == 5)
    {
        this->animateFullRotation();
    }
    
    if(this->obstacleType == 4 || this->obstacleType == 6 || this->obstacleType == 8 || this->obstacleType == 9)
    {
        this->animateBackNForth();
    }
    
    if ( this->obstacleType == 3)
    {
        this->animateScaling();
    }
    
    if (this->obstacleType == 7)
    {
        this->animateStrawberry();
    }
}

void FirstObstacle::update(float dt)
{
    
}

void FirstObstacle::onExit()
{
    //this->delegate = nullptr;
    
    this->Sprite::onExit();
}

void FirstObstacle::moveObstacle(){
    auto containerSize = Director::getInstance()->getVisibleSize();
    auto containerOrigin = Director::getInstance()->getVisibleOrigin();
    if(this->getPositionX() == -100 && this->getPositionY() == -100)
    {
        this->hasMoveEnded = true;
    }
    
    auto moveAction = MoveBy::create(5.0f, Vec2(-containerSize.width-500, 0)); //time was 10
    auto removeObstacle = CallFunc::create([&](){
        this->hasMoveEnded = true;
    });
    auto seqAction = Sequence::create(moveAction, removeObstacle, NULL);
    this->runAction(seqAction);
}

void FirstObstacle::animateFullRotation()
{
    if(this->getActionByTag(FULL_ROTATE)==nullptr)
    {
    auto rotateAction = RotateBy::create(2.5, -360);
 
    this->runAction(RepeatForever::create(rotateAction));
    }
}

void FirstObstacle::animateBackNForth()
{
        this->setAnchorPoint(Vec2(0,-this->getContentSize().height*0.5));
        auto rotateAction = RotateTo::create(0.4, 7);
        auto rotateAction2 = RotateTo::create(0.4, -7);
        auto seqAction = Sequence::create(rotateAction, rotateAction2, NULL);
        this->runAction(RepeatForever::create(seqAction));
    
}

void FirstObstacle::animateScaling()
{
    auto scaledown = ScaleTo::create(0.5, this->getScale()*0.4);
    auto scaleup = ScaleTo::create(0.5, this->getScale()*0.5);
    auto seqAction = Sequence::create(scaledown, scaleup, NULL);
    this->runAction(RepeatForever::create(seqAction));
    
}

void FirstObstacle::animateStrawberry()
{
    
        Vector< SpriteFrame *> animFrames(28);
    animFrames.pushBack(SpriteFrame::create("StrawberryCreature_1.png", Rect(0,0,252, 196)));
    animFrames.pushBack(SpriteFrame::create("StrawberryCreature_2.png", Rect(0,0,252, 196)));
    animFrames.pushBack(SpriteFrame::create("StrawberryCreature_3.png", Rect(0,0,252, 196)));
    animFrames.pushBack(SpriteFrame::create("StrawberryCreature_4.png", Rect(0,0,252, 196)));
    animFrames.pushBack(SpriteFrame::create("StrawberryCreature_5.png", Rect(0,0,252, 196)));
    animFrames.pushBack(SpriteFrame::create("StrawberryCreature_6.png", Rect(0,0,252, 196)));
    animFrames.pushBack(SpriteFrame::create("StrawberryCreature_7.png", Rect(0,0,252, 196)));
    animFrames.pushBack(SpriteFrame::create("StrawberryCreature_8.png", Rect(0,0,252, 196)));
    animFrames.pushBack(SpriteFrame::create("StrawberryCreature_9.png", Rect(0,0,252, 196)));
    animFrames.pushBack(SpriteFrame::create("StrawberryCreature_10.png", Rect(0,0,252, 196)));
    animFrames.pushBack(SpriteFrame::create("StrawberryCreature_11.png", Rect(0,0,252, 196)));
    animFrames.pushBack(SpriteFrame::create("StrawberryCreature_12.png", Rect(0,0,252, 196)));
    animFrames.pushBack(SpriteFrame::create("StrawberryCreature_13.png", Rect(0,0,252, 196)));
    animFrames.pushBack(SpriteFrame::create("StrawberryCreature_14.png", Rect(0,0,252, 196)));
    animFrames.pushBack(SpriteFrame::create("StrawberryCreature_15.png", Rect(0,0,252, 196)));
    animFrames.pushBack(SpriteFrame::create("StrawberryCreature_16.png", Rect(0,0,252, 196)));
    animFrames.pushBack(SpriteFrame::create("StrawberryCreature_17.png", Rect(0,0,252, 196)));
    animFrames.pushBack(SpriteFrame::create("StrawberryCreature_18.png", Rect(0,0,252, 196)));
    animFrames.pushBack(SpriteFrame::create("StrawberryCreature_19.png", Rect(0,0,252, 196)));
    animFrames.pushBack(SpriteFrame::create("StrawberryCreature_20.png", Rect(0,0,252, 196)));
    animFrames.pushBack(SpriteFrame::create("StrawberryCreature_21.png", Rect(0,0,252, 196)));
    animFrames.pushBack(SpriteFrame::create("StrawberryCreature_22.png", Rect(0,0,252, 196)));
    animFrames.pushBack(SpriteFrame::create("StrawberryCreature_23.png", Rect(0,0,252, 196)));
    animFrames.pushBack(SpriteFrame::create("StrawberryCreature_24.png", Rect(0,0,252, 196)));
    animFrames.pushBack(SpriteFrame::create("StrawberryCreature_25.png", Rect(0,0,252, 196)));
    animFrames.pushBack(SpriteFrame::create("StrawberryCreature_26.png", Rect(0,0,252, 196)));
    animFrames.pushBack(SpriteFrame::create("StrawberryCreature_27.png", Rect(0,0,252, 196)));
    animFrames.pushBack(SpriteFrame::create("StrawberryCreature_28.png", Rect(0,0,252, 196)));
        float animationRate = 0.03;
        Animation* animation = Animation::createWithSpriteFrames(animFrames, animationRate);
        Action * finalanimation = RepeatForever::create(Animate::create(animation));
        this->runAction(finalanimation);
   
}