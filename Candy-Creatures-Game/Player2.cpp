//
//  Player2.cpp
//  CandyCreatures
//
//  Created by moeezo saleem on 12/23/15.
//
//

#include "Player2.h"

#define MY_PLAYER_WALK_ANIM 2001
#define MY_PLAYER_BACK_ANIM 2002


Player2 * Player2::create()
{
    Player2 *view = new Player2();
    
    if (view && view->initWithFile("user_lvl2_01.png")){ 
        
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



void Player2::initialize()
{
    
    
    this->animatePlayerWalk();
    this->scheduleUpdate();
    
    
}

void Player2::update(float dt)
{
    
    
}

void Player2::onExit()
{
    //this->delegate = nullptr;
    
    this->Sprite::onExit();
}


void Player2::animatePlayerWalk()
{
    if(this->getActionByTag(MY_PLAYER_WALK_ANIM) == nullptr)
    {
        Vector< SpriteFrame *> animFrames(6);
        animFrames.pushBack(SpriteFrame::create("user_lvl2_01.png", Rect(0,0,188, 242)));
         animFrames.pushBack(SpriteFrame::create("user_lvl2_02.png", Rect(0,0,188, 242)));
         animFrames.pushBack(SpriteFrame::create("user_lvl2_03.png", Rect(0,0,188, 242)));
         animFrames.pushBack(SpriteFrame::create("user_lvl2_04.png", Rect(0,0,188, 242)));
         animFrames.pushBack(SpriteFrame::create("user_lvl2_05.png", Rect(0,0,188, 242)));
         animFrames.pushBack(SpriteFrame::create("user_lvl2_06.png", Rect(0,0,188, 242)));
        float animationRate = 0.1;
        Animation* animation = Animation::createWithSpriteFrames(animFrames, animationRate);
        Action * finalanimation = RepeatForever::create(Animate::create(animation));
        finalanimation->setTag(MY_PLAYER_WALK_ANIM);
        this->runAction(finalanimation);
    }
    
}


void Player2::stopAnimatePlayerWalk()
{
    if(this->getActionByTag(MY_PLAYER_WALK_ANIM))
    {
        this->stopActionByTag(MY_PLAYER_WALK_ANIM);
    }
    
}


void Player2::animatePlayerBackground()
{
    Sprite* bkground = Sprite::create("me1.png");
    bkground->setAnchorPoint(Vec2(0.5,0.5));
    float bgscale= this->getScale() *2.5;
    bkground->setScale(bgscale);
    float posX= this->getPositionX()+ (this->getContentSize().width*0.5);
    float posY= this->getPositionY()+ (this->getContentSize().height*0.5);
    bkground->setPosition(Vec2(posX, posY));
    
    this->bgSprite = bkground;
    this->addChild(this->bgSprite,-1);
    
    if(this->getActionByTag(MY_PLAYER_BACK_ANIM) == nullptr)
    {
        Vector< SpriteFrame *> animFrames(6);
        animFrames.pushBack(SpriteFrame::create("me1.png", Rect(0,0,151, 146)));
        animFrames.pushBack(SpriteFrame::create("me2.png", Rect(0,0,151, 146)));
        animFrames.pushBack(SpriteFrame::create("me3.png", Rect(0,0,151, 146)));
        animFrames.pushBack(SpriteFrame::create("me4.png", Rect(0,0,151, 146)));
        animFrames.pushBack(SpriteFrame::create("me5.png", Rect(0,0,151, 146)));
        animFrames.pushBack(SpriteFrame::create("me6.png", Rect(0,0,151, 146)));
        
        
        float animationRate = 0.04;
        Animation* animation = Animation::createWithSpriteFrames(animFrames, animationRate);
        Action * finalanimation = RepeatForever::create(Animate::create(animation));
        finalanimation->setTag(MY_PLAYER_BACK_ANIM);
        this->bgSprite->runAction(finalanimation);
    }
}



