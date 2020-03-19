//
//  Level1.cpp
//  CandyCreatures
//
//  Created by moeezo saleem on 12/17/15.
//
//

#include "Level1.h"
#include "Level2.h"
#include "MenuMap.h"

#define PLAYER_TAG 200
#define MONSTER_TAG 201
#define FOOD_TAG 202
#define BACKGROUND_TAG 203

#define BACKGROUND_Z_INDEX 5
#define PLAYER_Z_INDEX 50
#define MONSTER_Z_INDEX 52
#define FOOD_Z_INDEX 53

Level1* Level1::create() {
    Level1 *pRet = new Level1();
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

void Level1::addCRHud(){
    this->CRhud = CRHud::getInstance(this);
    this->addChild(this->CRhud, 100);
    this->CRhud->setDelegate(this);
    this->CRhud->hideOverlay();
}

void Level1::addWinScreen(){
    if(this->winScreen == nullptr)
    {
    
    this->winScreen = WinScreen::getInstance(this);
   
    this->addChild(this->winScreen, 101);
    this->winScreen->setDelegate(this); 
    this->winScreen->show();
    }
    else
    {
        this->winScreen->show();
        
    }
}


void Level1::WinScreenRestartButtonSelected(){
    CCLOG("The button restart for the win screen has been clicked and this is the result");
    this->winScreen->hide();
    this->resetVariables();
}
void Level1::resumeAllp(){
    this->scheduleUpdate();
    this->scheduleOnce(schedule_selector(Level1::levelComplete), this->gameDuration);
    this->resume();
    this->myPlayer->resume();
    this->myMonster->resume();
    this->myMonster->upAndDownMotion();
    this->myMonster->forwardMotion();
    this->myBackground->resume();
}
void Level1::resetVariables(){
    this->myMonster->stopAllActions();
    this->unschedule(schedule_selector(Level1::levelComplete));
    this->myMonster->hasWon = false;
    this->myMonster->isOutside = false;
    this->myMonster->timeOutside = 0;
    this->myMonster->shouldWalkStraight = false;
    this->myMonster->shouldCatchPlayer = false;
    this->CRhud->resetHud();
    this->CRhud->startTime();
    this->timePassed = 0;
    auto containerSize = Director::getInstance()->getVisibleSize();
    auto containerOrigin = Director::getInstance()->getVisibleOrigin();
    float monPosX= containerOrigin.x + this->myMonster->getBoundingBox().size.width +50;
    float monPosY= containerOrigin.y + (containerSize.height* 0.5) -(this->myMonster->getBoundingBox().size.height *0.5);
    this->myMonster->setPosition(Vec2(monPosX, monPosY));
    
    this->myPlayer->setScale((containerSize.width*0.18)/this->myPlayer->getContentSize().width);
    float playerPosX= containerOrigin.x + containerSize.width -( this->myPlayer->getBoundingBox().size.width* 0.5);
    float playerPosY = containerOrigin.y + (containerSize.height* 0.5) -(this->myPlayer->getBoundingBox().size.height *0.2);
    this->myPlayer->setPosition(Vec2(playerPosX, playerPosY));
    
    DelayTime *delayT = DelayTime::create(0.3);
    CallFunc *resumefunc =  CallFunc::create(CC_CALLBACK_0(Level1::resumeAllp, this));
    this->runAction(Sequence::create(delayT, resumefunc, NULL));

}

void Level1::WinScreenNextLevelButtonSelected(){
    CCLOG("The button next level for the win screen has been clicked and this is the result");
    stopAllActions();
    unscheduleAllSelectors();
    removeFromParentAndCleanup(true);
    auto scene = Level2::create();
    Director::getInstance()->replaceScene(scene);
    
}

void Level1::WinScreenHomeButtonSelected(){
    CCLOG("The home button for the win screen has been clicked and this is the result");
    stopAllActions();
    unscheduleAllSelectors();
    removeFromParentAndCleanup(true);
    auto scene = MenuMap::create();
    Director::getInstance()->replaceScene(scene);

}

void Level1::addLoseScreen(){
    if(this->loseScreen== nullptr)
    {
    this->loseScreen = LoseScreen::getInstance(this);
    this->addChild(this->loseScreen, 101);
    this->loseScreen->setDelegate(this);
    this->loseScreen->show();
    }
    else{
        this->loseScreen->show();
    }
    this->unscheduleUpdate();
    this->pause();
    this->myPlayer->pause();
    this->myMonster->pause();
    this->myBackground->pause();
    

}
void Level1::loseScreenRestartButtonSelected(){
    CCLOG("The restart button for the game lose screen has been clicked and this is the result");
    this->loseScreen->hide();
    this->resetVariables();
    
}

void Level1::loseScreenHomeButtonSelected(){
    CCLOG("The home button for the game lose screen has been clicked and this is the result");
}


bool Level1::init()
{
    //initialize the super first
    if ( !Scene::init() )
    {
        return false;
    }
    
    this->touchListener = EventListenerTouchOneByOne::create();
    this->touchListener->setSwallowTouches(true);
    this->touchListener->onTouchBegan = CC_CALLBACK_2(Level1::onTouchBegan, this);
    this->touchListener->onTouchMoved = CC_CALLBACK_2(Level1::onTouchMoved, this);
    this->touchListener->onTouchEnded = CC_CALLBACK_2(Level1::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    auto containerSize = Director::getInstance()->getVisibleSize();
    auto containerOrigin = Director::getInstance()->getVisibleOrigin();
    
    auto background = DrawNode::create();
    background->drawSolidRect(containerOrigin, containerSize, Color4F(0.8,0.5,0.5,0.75));
    this->addChild(background,0);
    
   
    
    srand((unsigned int)time(nullptr));
    this->timePassed = 0;
    this->gameDuration = 30;
    
    this->startLevel1(1);
    
    return true;
    
}

void Level1::startLevel1(float dt){
    
    auto containerSize = Director::getInstance()->getVisibleSize();
    auto containerOrigin = Director::getInstance()->getVisibleOrigin();
    
    
    Level1Background * bkground = Level1Background::create();
    bkground->setScaleY(containerSize.height/bkground->getContentSize().height);
    //bgsprite->setScaleX(containerSize.width*2/bgsprite->getContentSize().width);
    bkground->setAnchorPoint(Vec2(0,0));
    bkground->setPosition(containerOrigin+ Vec2(0,bkground->getBoundingBox().size.height*0.5));
    this->myBackground = bkground;
    this->addChild(this->myBackground, BACKGROUND_Z_INDEX, BACKGROUND_TAG);
    this->moveBackground();
    
    
    Player *player = Player::create();
    player->setScale((containerSize.width*0.18)/player->getContentSize().width);
    float playerPosX= containerOrigin.x + containerSize.width -( player->getBoundingBox().size.width* 0.5);
    float playerPosY = containerOrigin.y + (containerSize.height* 0.5) -(player->getBoundingBox().size.height *0.2);
    player->setPosition(Vec2(playerPosX, playerPosY));
    this->myPlayer= player;
    this->addChild(this->myPlayer, PLAYER_Z_INDEX, PLAYER_TAG);
    
    CandyMonster * monster = CandyMonster::create();
    monster->setScale((containerSize.width*0.18)/monster->getContentSize().width);
    float monPosX= containerOrigin.x + monster->getBoundingBox().size.width +50;
    float monPosY= containerOrigin.y + (containerSize.height* 0.5) -(monster->getBoundingBox().size.height *0.5);
    monster->setPosition(Vec2(monPosX, monPosY));
    this-> myMonster = monster;
    this->addChild(this->myMonster, MONSTER_Z_INDEX, MONSTER_TAG);
    

    
    
    Sprite* bar = Sprite::create("RedLoadingBar.png");
    bar->setAnchorPoint(Vec2(0,0));
    bar->setPosition(containerOrigin);
    float barScaleX= (containerSize.width)/ bar->getContentSize().width;
    float barScaleY= (containerSize.height*0.01)/ bar->getContentSize().height;
    bar->setScale(barScaleX, barScaleY);
    this->timeBar = bar;
    this->addChild(this->timeBar,99);
    
    this->addCRHud();
    this->CRhud->resetHud();
    this->CRhud->startTime();
    
   // this->createFood();
    
    this->scheduleOnce(schedule_selector(Level1::levelComplete), this->gameDuration);
    
    this->scheduleUpdate();
}



void Level1::moveBackground()
{
    auto containerOrigin = Director::getInstance()->getVisibleOrigin();
    this->myBackground->setPosition(containerOrigin+Vec2(0,this->myBackground->getBoundingBox().size.height*0.5));
    auto disX= this->myBackground->getContentSize().width*0.5;//
    //auto movePos = bgPos + Vec2(-disX,0);
    auto moveAction = MoveBy::create(6,Vec2(-disX,0));
    
    CallFunc * again = CallFunc::create([&](){
        this->moveBackground();
    });
    
    auto repeatAction = Sequence::create(  moveAction,again, NULL);
    this->myBackground->runAction(repeatAction);
}

Vec2 Level1::getRandomPos(){
    
    Size containerSize = Director::getInstance()->getVisibleSize();
    auto containerOrigin = Director::getInstance()->getVisibleOrigin();
    
    int containerW= floorf(containerSize.width);
    int containerH= floorf(containerSize.height);
    float randomX= rand() % containerW + 1;
    float randomY= rand() % containerH + 1;
    Vec2 pos= Vec2(randomX, randomY);
    
    
    return pos;
}

bool Level1::onTouchBegan(Touch * touch, Event * event){
    
    Vec2 touchLocation = touch->getLocation();
    return true;
}

void Level1::onTouchMoved (Touch *touch, Event *unused_event){
    
}
void Level1::onTouchEnded(Touch *touch, Event *unused_event){
    Vec2 touchLocation= touch->getLocation();
   
    this->throwFood(touchLocation);

    
}

void Level1::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void Level1::update(float dt)
{
    
    auto containerSize = Director::getInstance()->getVisibleSize();
    
    float scaleWidth = (float)timePassed/ this->gameDuration;
    this->timeBar->setScaleX((scaleWidth* containerSize.width)/ this->timeBar->getContentSize().width);
    
    timePassed =timePassed+dt;
    
    if(timePassed< this->gameDuration)
    {
       // CCLOG("Time passed is %4.2f", timePassed);
    }
    
    
    //////////a new food is created when used up
   
    this->checkFoodCollision();
    this->checkPlayerCollision();

    ////////win state if monster has been outof the screen for a while
    if(this->myMonster){
        if(this->myMonster->hasWon ==true)
        {
            CCLOG("You've won the game!");
            this->unscheduleUpdate();
            this->pause();
            this->myPlayer->pause();
            this->myMonster->pause();
            this->myBackground->pause();
            this->addWinScreen();
        }
        
    }
    
    
}

void Level1::levelComplete(float dt)
{
    this->unscheduleUpdate();
    this->myMonster->shouldWalkStraight = true;  //stops other actions on the monster
    //animate the player
   auto monsterFadeAction = FadeTo::create(1, 0);
   auto playerEndAction = CallFunc::create(CC_CALLBACK_0(Level1::playerEndGameAction, this));
    auto delayAction = DelayTime::create(1);
    auto gameOverAction = CallFunc::create(CC_CALLBACK_0(Level1::gameOverWinAction, this));
    this->myMonster->runAction(Sequence::create(monsterFadeAction, playerEndAction, delayAction, gameOverAction, nullptr));

}

void Level1::playerEndGameAction()
{
    auto winOrigin = Director::getInstance()->getVisibleOrigin();
    auto winSize = Director::getInstance()->getVisibleSize();
    
    auto playerRotate = CallFunc::create([&](){
      this->myPlayer->setScaleX(this->myPlayer->getScaleX()*-1);
    });
    auto playerMoveAction = MoveTo::create(2, Vec2(winOrigin.x+ winSize.width *0.5, winOrigin.y + winSize.height * 0.5));
    this->myPlayer->runAction(Sequence::create(playerRotate, playerMoveAction, NULL));
}


void Level1::gameOverWinAction()
{
    this->stopAllActions();
    this->pause();
    this->myPlayer->pause();
    this->myMonster->pause();
    this->myBackground->pause();
    this->addWinScreen();
}


void Level1::createFood(){
    if (this->foodToThrow == nullptr && this->getChildByTag(FOOD_TAG)== NULL)
    {
        auto containerSize = Director::getInstance()->getVisibleSize();
        Sprite* food = Sprite::create("Candy_toThrow.png");
        food->setAnchorPoint(Vec2(0.5,0.5));
        food->setScale((containerSize.width * 0.03)/ food->getContentSize().width);
        food->setPosition(Vec2(this->myPlayer->getPositionX()- this->myPlayer->getBoundingBox().size.width*0.5, this->myPlayer->getPositionY()));
        food->setRotation(90);
        this-> foodToThrow = food;
        this->addChild(this->foodToThrow,FOOD_Z_INDEX, FOOD_TAG);
        this->foodToThrow->setVisible(false);
        CCLOG("a new food has been created!");

    }
}

void Level1::throwFood(Vec2 pos)
{
    this->createFood();
    if(this->foodToThrow!= nullptr && this->getChildByTag(FOOD_TAG)!= NULL){
        
    
        this->foodToThrow->setVisible(true);
    
        auto moveFoodAction = MoveTo::create(0.3,pos);
        auto rotateFoodAction = RotateBy::create(0.3, -90);
        auto scaleFoodAction = ScaleTo::create(0.3, this->foodToThrow->getScale()*1.2);
    
        auto visibilityAction = FadeOut::create(0.2);

        
        CallFunc* removeTagForFood = CallFunc::create([&](){
            if(this->getChildByTag(FOOD_TAG)){
                this->removeChildByTag(FOOD_TAG);
            }
            this->foodToThrow = nullptr;
            //CCLOG("child removed!");
        });
    
        auto foodSeq = Sequence::create(Spawn::create(moveFoodAction, rotateFoodAction, scaleFoodAction, nullptr), visibilityAction, removeTagForFood, NULL);
    
        this->foodToThrow->runAction(foodSeq);
    }
}

void Level1::checkFoodCollision(){
    if(this->foodToThrow!= nullptr){
        Rect foodRect = this->foodToThrow->getBoundingBox();
        Rect monRect = this->myMonster->getBoundingBox();
        
        if(monRect.intersectsRect(foodRect))
        {
            if(this->myMonster->isHit == false){
                this->myMonster->isHit = true;
                this->myMonster->hitCount =1;
            }
            else
            {
                this->myMonster->hitCount+= 1;
            }
            CCLOG("monster has been hit");
        }
        
    }
}

void Level1::checkPlayerCollision(){
    if(this->myPlayer!=nullptr && this->myMonster!=nullptr)
    {
        float offsetX = Director::getInstance()->getVisibleSize().width * 0.08;
        float playerOriginalX = this->myPlayer->getBoundingBox().getMinX();
        float posX = playerOriginalX - offsetX;
        
        if(this->myMonster->getPositionX() > posX) //if monster gets too close to the player it moves forward
        {
            this->myMonster->shouldWalkStraight = true;// this will stop upAndDown and forward moves
        }
        
        if(this->myMonster->shouldCatchPlayer == true)  //when other actions stop the monster can move forward
        {
            auto monMove = MoveTo::create(5, this->myPlayer->getPosition());
            this->myMonster->runAction(monMove);
            
        }
        
        Rect monRect = this->scaleRectangle(this->myMonster->getBoundingBox(), 0.8, 0.8);
        Rect playerRect = this->scaleRectangle(this->myPlayer->getBoundingBox(), 0.7, 0.7);
        
        if( monRect.intersectsRect(playerRect))
        {
            //this->unscheduleUpdate();
            this->pause();
            this->addLoseScreen();
            CCLOG("Monster caught you!");
        }
    }
}

Rect Level1::scaleRectangle( Rect rec, float scaleX, float scaleY){
    float playerW= rec.size.width * scaleX;
    float playerH= rec.size.height * scaleY;
    float playerX= rec.getMidX() - (playerW * 0.5);
    float playerY= rec.getMidY()- (playerH * 0.5);
    Rect newRect = Rect(playerX, playerY, playerW, playerH);
    return newRect;
}