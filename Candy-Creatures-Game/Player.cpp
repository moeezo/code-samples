//
//  Player.cpp
//  CandyCreatures
//
//  Created by moeezo saleem on 12/14/15.
//
//

#include "Player.h"

#define MY_PLAYER_WALK_ANIM 2001
#define MY_PLAYER_BACK_ANIM 2002
#define FREEZE_GUN_ANIM 2003

Player * Player::create()
{
    Player *view = new Player();
    
    if (view && view->initWithFile("user_01.png")){  
        
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



void Player::initialize()
{
    
  
    this->animatePlayerWalk();
    this->scheduleUpdate();
  
}

void Player::update(float dt)
{
    

}

void Player::onExit()
{
    //this->delegate = nullptr;
    
    this->Sprite::onExit();
}


void Player::animatePlayerWalk()
{
    if(this->getActionByTag(MY_PLAYER_WALK_ANIM) == nullptr)
    {
        Vector< SpriteFrame *> animFrames(6);
        animFrames.pushBack(SpriteFrame::create("user_01.png", Rect(0,0,300, 242)));
        animFrames.pushBack(SpriteFrame::create("user_02.png", Rect(0,0,300, 242)));
        animFrames.pushBack(SpriteFrame::create("user_03.png", Rect(0,0,300, 242)));
        animFrames.pushBack(SpriteFrame::create("user_04.png", Rect(0,0,300, 242)));
        animFrames.pushBack(SpriteFrame::create("user_05.png", Rect(0,0,300, 242)));
        animFrames.pushBack(SpriteFrame::create("user_06.png", Rect(0,0,300, 242)));
        float animationRate = 0.1;
        Animation* animation = Animation::createWithSpriteFrames(animFrames, animationRate);
        Action * finalanimation = RepeatForever::create(Animate::create(animation));
        finalanimation->setTag(MY_PLAYER_WALK_ANIM);
        this->runAction(finalanimation);
     }
    
}


void Player::stopAnimatePlayerWalk()
{
    if(this->getActionByTag(MY_PLAYER_WALK_ANIM))
    {
        this->stopActionByTag(MY_PLAYER_WALK_ANIM);
    }

}


void Player::animatePlayerBackground()
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



