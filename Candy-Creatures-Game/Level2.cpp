//
//  Level2.cpp
//  Candy Creatures
//
//  Created by moeezo saleem on 12/1/15.
//
//

#include "Level2.h"

#define MY_PLAYER_TAG 300
#define BKGROUND_TAG 301
#define OBSTACLE_TAG 302

#define MY_PLAYER_ZINDEX  50
#define BKGROUND_ZINDEX  5
#define OBSTACLE_ZINDEX  55

Level2* Level2::create() {
    Level2 *pRet = new Level2();
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

void Level2::addCRHud(){
    this->CRhud = CRHud::getInstance(this);
   // this->addChild(this->CRhud, 100);
    this->CRhud->setDelegate(this);
    this->CRhud->hideOverlay();
}

void Level2::addWinScreen(){
    
        this->winScreen = WinScreen::getInstance(this);
       
        this->addChild(this->winScreen, 101);
        this->winScreen->setDelegate(this);
        this->winScreen->show();
}


void Level2::WinScreenRestartButtonSelected(){
    CCLOG("The button restart for the win screen has been clicked and this is the result");
}

void Level2::WinScreenNextLevelButtonSelected(){
    CCLOG("The button next level for the win screen has been clicked and this is the result");
}

void Level2::WinScreenHomeButtonSelected(){
    CCLOG("The home button for the win screen has been clicked and this is the result");
}

void Level2::addLoseScreen(){
    this->loseScreen = LoseScreen::getInstance(this);
    this->addChild(this->loseScreen, 101);
    this->loseScreen->setDelegate(this);
    this->loseScreen->show();
}
void Level2::loseScreenRestartButtonSelected(){
    CCLOG("The restart button for the game lose screen has been clicked and this is the result");
}

void Level2::loseScreenHomeButtonSelected(){
    CCLOG("The home button for the game lose screen has been clicked and this is the result");
}

bool Level2::init()
{
    //initialize the super first
    if ( !Scene::init() )
    {
        return false;
    }
    
    this->touchListener = EventListenerTouchOneByOne::create();
    this->touchListener->setSwallowTouches(true);
    this->touchListener->onTouchBegan = CC_CALLBACK_2(Level2::onTouchBegan, this);
     this->touchListener->onTouchMoved = CC_CALLBACK_2(Level2::onTouchMoved, this);
     this->touchListener->onTouchEnded = CC_CALLBACK_2(Level2::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    auto containerSize = Director::getInstance()->getVisibleSize();
    auto containerOrigin = Director::getInstance()->getVisibleOrigin();
    
    auto background = DrawNode::create();
    background->drawSolidRect(containerOrigin, containerSize, Color4F(0.8,0.5,0.5,0.75));
    this->addChild(background,0);
    
    
     srand((unsigned int)time(nullptr));
    this->timePassed = 0;
    this->gameDuration = 25;  //duration was 40
    
    
    this->startLevel2(1);
  
    return true;

}

void Level2::startLevel2(float dt){

    
    auto containerSize = Director::getInstance()->getVisibleSize();
    auto containerOrigin = Director::getInstance()->getVisibleOrigin();
    
    this->heightRandomOffset= containerSize.height * 0.06;  //for ipad its 124
    this->hasDragged = false;
    this->movePlayerToFinishLine = false;
    
  
    
    Level1Background * bkground = Level1Background::create();
    bkground->setScaleY(containerSize.height/bkground->getContentSize().height);
    bkground->setAnchorPoint(Vec2(0,0));
    bkground->setPosition(containerOrigin+ Vec2(0,bkground->getBoundingBox().size.height*0.5));
    this->myBackground = bkground;
    this->addChild(this->myBackground, BKGROUND_ZINDEX, BKGROUND_TAG);
    this->moveBackground();
    
    
    Player2* player = Player2::create();
    player->setScale((containerSize.width * 0.1)/player->getContentSize().width);
    float pPosX= containerOrigin.x + player->getBoundingBox().size.width + containerSize.width*0.1;
    float pPosY= containerOrigin.y + containerSize.height*0.5 - player->getBoundingBox().size.height*0.5;
    player->setPosition(Vec2(pPosX, pPosY));
    this->myPlayer = player;
    this->addChild(this->myPlayer, MY_PLAYER_ZINDEX, MY_PLAYER_TAG);
    
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
    this->schedule(schedule_selector(Level2::addObstacle), 2 );
    this->schedule(schedule_selector(Level2::addObstacle1), 7 );
    this->schedule(schedule_selector(Level2::addObstacle2), 5 );
    this->schedule(schedule_selector(Level2::addObstacle3), 3 );
    //this->addObstacle3(1);
    this->scheduleOnce(schedule_selector(Level2::levelComplete), this->gameDuration);
    
    this->scheduleUpdate();
}

void Level2::moveBackground()
{
    auto containerOrigin = Director::getInstance()->getVisibleOrigin();
    this->myBackground->setPosition(containerOrigin+Vec2(0,this->myBackground->getBoundingBox().size.height*0.5));
    auto disX= this->myBackground->getContentSize().width*0.5;//
    //auto movePos = bgPos + Vec2(-disX,0);
    auto moveAction = MoveBy::create(8,Vec2(-disX,0)); 
    
    CallFunc * again = CallFunc::create([&](){
        this->moveBackground();
    });
    
    auto repeatAction = Sequence::create(  moveAction,again, NULL);
    this->myBackground->runAction(repeatAction);
}

void Level2::addObstacle(float dt){
    auto containerSize = Director::getInstance()->getVisibleSize();
    int randomType = rand() % 7 + 1;
    FirstObstacle* ob1 = FirstObstacle::createWithType(randomType);
    ob1->setAnchorPoint(Vec2(0.5, 0.5));
    if(randomType== 4 || randomType == 6 || randomType == 7)
    {
        ob1->setScale((containerSize.height*0.19)/ob1->getContentSize().height);     //width* 0.1
    }
    else if (randomType == 3)
    {
        ob1->setScale((containerSize.height*0.22)/ob1->getContentSize().height);   //width * 0.16
    }
    else
    {
        ob1->setScale((containerSize.height*0.16)/ob1->getContentSize().height);  //width * 0.12
    }
    
    ob1->setPosition(this->getRandomPos());
    this->addChild(ob1,OBSTACLE_ZINDEX, OBSTACLE_TAG);
    this->Obstacles.pushBack(ob1);
    ob1->moveObstacle();

}

void Level2::addObstacle1(float dt){
    auto containerSize = Director::getInstance()->getVisibleSize();
    int randomType = rand() % 7 + 1;
    FirstObstacle* ob1 = FirstObstacle::createWithType(randomType);
    ob1->setAnchorPoint(Vec2(0.5, 0.5));
    
    if(randomType== 4 || randomType == 6 || randomType == 7)
    {
        ob1->setScale((containerSize.height*0.19)/ob1->getContentSize().height);     //width* 0.1
    }
    else if (randomType == 3)
    {
        ob1->setScale((containerSize.height*0.22)/ob1->getContentSize().height);   //width * 0.16
    }
    else
    {
        ob1->setScale((containerSize.height*0.16)/ob1->getContentSize().height);  //width * 0.12
    }
    
  
    ob1->setPosition(this->getRandomPos());
    this->addChild(ob1,OBSTACLE_ZINDEX, OBSTACLE_TAG);
    this->Obstacles.pushBack(ob1);
    ob1->moveObstacle();
    
}

void Level2::addObstacle2(float dt){
    auto containerSize = Director::getInstance()->getVisibleSize();
    int randomType = rand() % 7 + 1;
    FirstObstacle* ob1 = FirstObstacle::createWithType(randomType);
    ob1->setAnchorPoint(Vec2(0.5, 0.5));
    if(randomType== 4 || randomType == 6 || randomType == 7)
    {
        ob1->setScale((containerSize.height*0.19)/ob1->getContentSize().height);     
    }
    else if (randomType == 3)
    {
        ob1->setScale((containerSize.height*0.21)/ob1->getContentSize().height);   
    else
    {
        ob1->setScale((containerSize.height*0.16)/ob1->getContentSize().height);  
    }
    
    ob1->setPosition(this->getRandomPos());
    this->addChild(ob1,OBSTACLE_ZINDEX, OBSTACLE_TAG);
    this->Obstacles.pushBack(ob1);
    ob1->moveObstacle();
    
}

void Level2::addObstacle3(float dt){
    auto containerSize = Director::getInstance()->getVisibleSize();
    int randomType = rand() % 2 + 8;
    FirstObstacle* ob1 = FirstObstacle::createWithType(randomType);
    ob1->setAnchorPoint(Vec2(0.5, 0.5));
    ob1->setScaleX((containerSize.width*0.12)/ob1->getContentSize().width);
    ob1->setScaleY(containerSize.height * 0.24/ob1->getContentSize().height);
    Vec2 randomPos = this->getRandomPos2();
    CCLOG("The random Position generated is %f, %f", randomPos.x, randomPos.y);
    ob1->setPosition(randomPos);
    this->addChild(ob1,OBSTACLE_ZINDEX, OBSTACLE_TAG);
    this->Obstacles.pushBack(ob1);
    ob1->moveObstacle();
    
}

Vec2 Level2::getRandomPos(){
    
    Size containerSize = Director::getInstance()->getVisibleSize();
    auto containerOrigin = Director::getInstance()->getVisibleOrigin();
    float mainHeight= containerSize.height;
    int randomY= rand() % 3 + 1;
    float posY;
      if(randomY == 1)
      {
          posY = containerOrigin.y + (0.22)* mainHeight;   //0.2065
      }
     else if (randomY == 2)
      {
        posY = containerOrigin.y + (0.4995)* mainHeight;    //0.4995
      }
     else if (randomY == 3)
      {
        posY = containerOrigin.y + (0.76)* mainHeight;  //0.7925
      }
    
    float fixedX = containerOrigin.x + containerSize.width + 400;
    
    Vec2 pos= Vec2(fixedX, posY);
    float posW= 320;
    float posH=322;
    float posOriginX= fixedX - posW*0.5;
    float posOriginY= posY - posH*0.5;
    Rect positionRect = Rect(posOriginX, posOriginY, posW, posY);
    
    if(this->Obstacles.size() > 0){
        for(int i=0; i< Obstacles.size(); i++)
        {
            Sprite* ob = Obstacles.at(i);
            if(ob->getBoundingBox().intersectsRect(positionRect))    //.containsPoint(pos)
            {
               //if(!isScheduled(schedule_selector(Level2::delayRandomPositionCheck)))
                //{
                    //CCLOG("Scheduling a new position 2!");
                    //this->scheduleOnce(schedule_selector(Level2::delayRandomPositionCheck), 3);
                   return Vec2(-100, -100);
                //}
            }
        }
    }
    
    return pos;
}

Vec2 Level2::getRandomPos2(){
    
    Size containerSize = Director::getInstance()->getVisibleSize();
    auto containerOrigin = Director::getInstance()->getVisibleOrigin();
    float mainHeight= containerSize.height;
    CCLOG("main window size is %f. %f", containerSize.width, mainHeight);
    CCLOG("main window origin is %f, %f", containerOrigin.x, containerOrigin.y);
    int randomY= rand() % 2 + 1;
    CCLOG("value of random number is %d", randomY);
    float posY = 100;
    if(randomY == 1)
    {
        posY = containerOrigin.y + (0.3)* mainHeight;//prev was 35.3/100 * mainHeight
        CCLOG("The random Y1 generated is %f", posY);
    }
    else if (randomY == 2)
    {
        posY = containerOrigin.y + (0.7)* mainHeight;
        CCLOG("The random Y2 generated is %f", posY); //prev was 64.6/100 * mainHeight
    }
  
    
    float fixedX = containerOrigin.x + containerSize.width + 400;
    
    Vec2 pos= Vec2(fixedX, posY);
    float posW= 320;
    float posH=322;
    float posOriginX= fixedX - posW*0.5;
    float posOriginY= posY - posH*0.5;
    Rect positionRect = Rect(posOriginX, posOriginY, posW, posY);
    
    if(this->Obstacles.size() > 0){
        for(int i=0; i< Obstacles.size(); i++)
        {
            Sprite* ob = Obstacles.at(i);
            if(ob->getBoundingBox().intersectsRect(positionRect))   //containsPoint(pos)
            {
               // if(!isScheduled(schedule_selector(Level2::delayRandomPositionCheck)))
               // {
                //    CCLOG("Scheduling a new position 2!");
                 //   this->scheduleOnce(schedule_selector(Level2::delayRandomPositionCheck), 4);
                return Vec2(-100,-100);
               // }
            }
        }
    }
   
    return pos;
}


bool Level2::onTouchBegan(Touch * touch, Event * event){
   
    Vec2 touchLocation = touch->getLocation();
    this->initialTouch = touchLocation;
    this->finalTouch = touchLocation;
    this->hasDragged = false;
    return true;
}

void Level2::onTouchMoved (Touch *touch, Event *unused_event){
    Vec2 touchLocation = touch->getLocation();
    this->finalTouch = touchLocation;
    this->hasDragged = true;
}

void Level2::onTouchEnded(Touch *touch, Event *unused_event){
    auto containerSize = Director::getInstance()->getVisibleSize();
    Vec2 touchLocation = touch->getLocation();
    this->finalTouch = touchLocation;
    float oldY= this->initialTouch.y;
    float newY = touchLocation.y;
    float diffY = newY- oldY;
    float diffYScaler = (diffY>0)? diffY : -diffY;
    if(diffYScaler > containerSize.height *0.1){
        this->hasDragged = true;
    }
    else
    {
        this->hasDragged = false;
    }
}


void Level2::movePlayerUp(){
    auto containerSize = Director::getInstance()->getVisibleSize();
    auto containerOrigin = Director::getInstance()->getVisibleOrigin();
    float upperBound = containerOrigin.y + containerSize.height - this->heightRandomOffset;
    float currY = this->myPlayer->getPositionY(); // + this->myPlayer->getBoundingBox().size.height *0.5;
    float nextY = (containerSize.height * 0.29) + currY;
    float moveY = (containerSize.height* 0.29)+ this->myPlayer->getPositionY();
    if(nextY < upperBound)
    {
        this->myPlayer->setPosition(Vec2(this->myPlayer->getPositionX(),moveY));
    }

}
void Level2::movePlayerDown(){
    auto containerSize = Director::getInstance()->getVisibleSize();
    auto containerOrigin = Director::getInstance()->getVisibleOrigin();
    float lowerBound = containerOrigin.y +  this->heightRandomOffset;
    float currY = this->myPlayer->getPositionY(); 
    float nextY = currY -(containerSize.height * 0.29);
    float moveY =  this->myPlayer->getPositionY() - (containerSize.height* 0.29);
    if(nextY > lowerBound)
    {
        this->myPlayer->setPosition(Vec2(this->myPlayer->getPositionX(),moveY));
    }
}

void Level2::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void Level2::update(float dt){
    
    auto containerSize = Director::getInstance()->getVisibleSize();
    auto containerOrigin= Director::getInstance()->getVisibleOrigin();
   
    float scaleWidth = (float)timePassed/ this->gameDuration;
    this->timeBar->setScaleX((scaleWidth* containerSize.width)/ this->timeBar->getContentSize().width);
    
    timePassed =timePassed+dt;
    
    if(timePassed<  this->gameDuration)
    {
   // CCLOG("Time passed is %4.2f", timePassed);
    }
    
    ///////////////check player collison with objects
    this->checkPlayerCollisionWithObstacle();
    
    //////check which objs have completed move and erase them
    if(this->Obstacles.size()> 0)
    {
        for(int i=0; i< this->Obstacles.size(); i++)
        {
            FirstObstacle * ob = this->Obstacles.at(i);
            if(ob->hasMoveEnded == true){
                this->removeChild(ob);
                this->Obstacles.eraseObject(ob);
                CCLOG("the obstacle has been erased");
            }
        }
    }
    /////////////////implement drag function
    if(this->myPlayer!= nullptr){
        this->dragPlayer();
    }
    
    ////////move player to finish line when the game time is over
    if(this->myPlayer!= nullptr && this->movePlayerToFinishLine == true){
        float posX = containerOrigin.x + containerSize.width* 0.5;
        auto movePlayer = MoveBy::create(8, Vec2(posX, 0));
        this->myPlayer->runAction(movePlayer);
    }
   
    
    //////////////if finishLine has been crossed
    if(this->levelFinishLine!=nullptr && this->myPlayer!=nullptr)
    {
        Rect playerRect = this->scaleRectangle(this->myPlayer->getBoundingBox(), 1, 0.95);
        Rect lineRect = this->scaleRectangle(this->levelFinishLine->getBoundingBox(), 1 , 1);
        if(playerRect.intersectsRect(lineRect)){
            this->unscheduleUpdate();
            this->pause();
            this->myPlayer->pause();
            this->myBackground->pause();
            this->CRhud->pauseTime();
            this->addWinScreen();
        }
    }
    
}

void Level2::dragPlayer(){
    
    if( this->hasDragged == true){
        float moveFactor = 4;
     
        float diffY = this->finalTouch.y - this->myPlayer->getPositionY();
     
        float diffYScaler = (diffY>0)? diffY : -diffY;
        
        if (diffYScaler >= moveFactor)
        {
            Vec2 curPos= this->myPlayer->getPosition();
            
            float moveY = this->myPlayer->getPositionY() + (diffY/moveFactor);
          
            this->myPlayer->setPosition(Vec2(curPos.x,moveY));
            
        }
        else
        {
            //do something here that happens when the player stops
            //this->stopAnimatePlayer();
            //this->myPlayer->isIdle = true;
        }
    }
    
}


void Level2::levelComplete(float dt){
   //unschedule all obstacles
    this->unschedule(schedule_selector(Level2::addObstacle));
    this->unschedule(schedule_selector(Level2::addObstacle1));
    this->unschedule(schedule_selector(Level2::addObstacle2));
    this->unschedule(schedule_selector(Level2::addObstacle3));
   
    this->scheduleOnce(schedule_selector(Level2::createFinishLine), 5);
    
}

void Level2::createFinishLine(float dt)
{
    Sprite * finishLine = Sprite::create("finish_line.png");
    finishLine->setAnchorPoint(Vec2(0,0));
    auto winSize = Director::getInstance()->getVisibleSize();
    auto winOrigin = Director::getInstance()->getVisibleOrigin();
    finishLine->setScaleY(Director::getInstance()->getVisibleSize().height/ finishLine->getContentSize().height);
    finishLine->setScaleX(Director::getInstance()->getVisibleSize().width*0.01/ finishLine->getContentSize().width);
    float fixedX = winOrigin.x + winSize.width + 400;
    finishLine->setPosition(Vec2(fixedX, winOrigin.y));
    this->levelFinishLine = finishLine;
    this->addChild(this->levelFinishLine, OBSTACLE_ZINDEX);
    
    float posX = winOrigin.x + (winSize.width*0.5) - (finishLine->getContentSize().width*0.5);
    auto movePlayerAction = CallFunc::create([&](){
        this->movePlayerToFinishLine = true;
      
    });
    auto moveLine = MoveBy::create(5, Vec2(-posX-500, 0));
    auto moveSeq= Sequence::create(moveLine, movePlayerAction, NULL);
    this->levelFinishLine->runAction(moveSeq);
}

void Level2::checkPlayerCollisionWithObstacle(){
    if(this->Obstacles.size()>0)
    {
        for (int i=0; i< this->Obstacles.size(); i++)
        {
            FirstObstacle * ob = this->Obstacles.at(i);
            Rect obRect = scaleRectangle(ob->getBoundingBox(), 0.5, 0.5);
            if(this->myPlayer)
            {
                Rect playerRect = scaleRectangle(this->myPlayer->getBoundingBox(), 0.6, 0.6);
                if(playerRect.intersectsRect(obRect))
                {
                    this->unscheduleUpdate();
                    this->pause();
                    this->myPlayer->pause();
                    this->addLoseScreen();
                }
            }
            
        }
        
    }
}

Rect Level2::scaleRectangle( Rect rec, float scaleX, float scaleY){
    float playerW= rec.size.width * scaleX;
    float playerH= rec.size.height * scaleY;
    float playerX= rec.getMidX() - (playerW * 0.5);
    float playerY= rec.getMidY()- (playerH * 0.5);
    Rect newRect = Rect(playerX, playerY, playerW, playerH);
    return newRect;
}
