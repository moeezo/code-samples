//
//  Level1Background.cpp
//  CandyCreatures
//
//  Created by moeezo saleem on 12/17/15.
//
//

#include "Level1Background.h"



Level1Background * Level1Background::create()
{
    Level1Background *view = new Level1Background();
    
    if (view && view->init()){  
        
        view->setAnchorPoint(Vec2(0, 0));
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



void Level1Background::initialize()
{
    this->bgSprite1 = Sprite::create("ingame bg_01.png");
    this->bgSprite1->setPosition(this->getPosition());
    this->addChild(this->bgSprite1);
    this->setContentSize(this->bgSprite1->getContentSize());
    this->bgSprite2 = Sprite::create("ingame bg_01.png");
    this->bgSprite2->setPosition(Vec2(this->getPositionX()+ this->getContentSize().width, this->getPositionY()));
    this->addChild(this->bgSprite2);
    this->setContentSize(Size(this->getContentSize().width+ this->bgSprite2->getContentSize().width, this->getContentSize().height));
    //this->scheduleUpdate();
    
    
}

void Level1Background::update(float dt)
{
    
    
}

void Level1Background::onExit()
{
    //this->delegate = nullptr;
    
    this->Sprite::onExit();
}






