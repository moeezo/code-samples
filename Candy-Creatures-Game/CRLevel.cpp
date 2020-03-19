//
//  CRLevel.cpp
//  CandyCreatures
//
//  Created by moeezo saleem on 12/28/15.
//
//

#include "CRLevel.h"

int CRLevel::getLevelType()
{
    return CRSingleton::getInstance()->getCurrentLevelData()->getLevelId();
}

float CRLevel::getBestPossibleTime()
{
    return CRSingleton::getInstance()->getCurrentLevelData()->getBestTime();
}

void CRLevel::addCRHud(){
    this->CRhud = CRHud::getInstance(this);
    this->addChild(this->CRhud, 1000);
    this->CRhud->setDelegate(this);
    this->CRhud->hideOverlay();
}

void CRLevel::addWinScreen(){
    
    this->winScreen = WinScreen::getInstance(this);
   
    this->addChild(this->winScreen, 1001);
    this->winScreen->setDelegate(this); 
    this->winScreen->show();
}


void CRLevel::addTutorialScreen(){
    
    this->tutorialScreen = TutorialScreen::getInstance(this);
    this->addChild(this->tutorialScreen, 1001);
    this->tutorialScreen->setDelegate(this); 
    this->tutorialScreen->show();
}


void CRLevel::addLoseScreen(){
    this->loseScreen = LoseScreen::getInstance(this);
    this->addChild(this->loseScreen, 1001);
    this->loseScreen->setDelegate(this);
    this->loseScreen->show();
}




void CRLevel::addTouchListener()
{
    removeTouchListener();
    this->touchListener = EventListenerTouchOneByOne::create();
    this->touchListener->setSwallowTouches(false);
    this->touchListener->onTouchBegan = CC_CALLBACK_2(CRLevel::onTouchBegan, this);
    this->touchListener->onTouchMoved = CC_CALLBACK_2(CRLevel::onTouchMoved, this);
    this->touchListener->onTouchEnded = CC_CALLBACK_2(CRLevel::onTouchEnded, this);
    this->touchListener->onTouchCancelled = CC_CALLBACK_2(CRLevel::onTouchCancelled, this);
    
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(this->touchListener, this);
}

void CRLevel::removeTouchListener()
{
    if (this->touchListener == nullptr)
    {
        return;
    }
    
    this->_eventDispatcher->removeEventListener(this->touchListener);
    this->touchListener = nullptr;
}

void CRLevel::addAccelerometerListener()
{
    Device::setAccelerometerEnabled(true);
    
    Device::setAccelerometerInterval(1.0/30.0);
    
    this->acclerationListener = EventListenerAcceleration::create(CC_CALLBACK_2(CRLevel::onAcceleration, this));
    this->acclerationListener->retain();
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(this->acclerationListener, this);
}

void CRLevel::removeAccelerometerListener()
{
    if (this->acclerationListener == nullptr)
    {
        return;
    }
    
    this->_eventDispatcher->removeEventListener(this->acclerationListener);
    this->acclerationListener->release();
    this->acclerationListener = nullptr;
}



void CRLevel::onEnter()
{
    this->Node::onEnter();
    this->levelSetup();
}

void CRLevel::onExit()
{
    this->removeAccelerometerListener();
    this->removeTouchListener();
    
    this->Node::onExit();
}

//Level Life Cycle


void CRLevel::levelSetup()
{
    
    this->addTutorialScreen();
    this->tutorialScreen->show();
   
  
}

void CRLevel::levelPause()
{
    this->CRhud->pauseTime();
    this->gamePaused = true;
    
    this->pause();
    
    for ( Node *ch : this->getChildren())
    {
    
        ch->pause();
        
        for ( Node *c : ch->getChildren())
        {
            c->pause();
        }
    }
}

void CRLevel::levelResume()
{
    this->CRhud->resumeTime();
    this->gamePaused = false;
    
    this->resume();
    
    for ( Node *ch : this->getChildren())
    {
        ch->resume();
        
        for ( Node *c : ch->getChildren())
        {
            c->resume();
        }
    }
}

void CRLevel::levelLost()
{
    this->levelPause();
    this->CRhud->stopTime();
    this->addLoseScreen();
}

void CRLevel::levelWon()
{
    this->levelPause();
    this->CRhud->stopTime();
    this->addWinScreen();
}

void CRLevel::levelRestart()
{
  
    if (this->gamePaused)
    {
        this->levelResume();
    }
    //decrease life count before resetting the hud
    this->CRhud->resetHud();
    
}

void CRLevel::levelStart()
{
    this->tutorialScreen->hide();
    this->addCRHud();
    
    this->CRhud->resetHud();
    this->CRhud->startTime();
}

//Touch Listener
bool CRLevel::onTouchBegan(Touch *touch, Event *event)
{
    if (this->gamePaused)
    {
        return false;
    }
    
    return true;
}

void CRLevel::onTouchMoved(Touch *touch, Event *event)
{
    
}

void CRLevel::onTouchEnded(Touch *touch, Event *event)
{
    
}

void CRLevel::onTouchCancelled(Touch *touch, Event *event)
{
    
}

//Accelerometer Listener
void CRLevel::onAcceleration(Acceleration *acc, Event *event)
{
    
}


//////////////////////////////////////////////////////////////

//Win Menu delegate
void CRLevel::WinScreenRestartButtonSelected(){
    CCLOG("The button restart for the win screen has been clicked and this is the result");
    this->winScreen->hide();
    this->levelRestart();
}

void CRLevel::WinScreenNextLevelButtonSelected(){
    CCLOG("The button next level for the win screen has been clicked and this is the result");
    //Do the unlocking of next level and transition of the scene for the next level here
}

void CRLevel::WinScreenHomeButtonSelected(){
    CCLOG("The home button for the win screen has been clicked and this is the result");
    auto newScene = MenuMap::create();
    Director *currentDirector = Director::getInstance();
    
    if (currentDirector->getRunningScene())
    {
        TransitionFade *transition = TransitionFade::create(0.3, newScene);
        currentDirector->replaceScene(transition);
    }
    else
    {
        currentDirector->runWithScene(newScene);
    }
    
}


void CRLevel::loseScreenRestartButtonSelected(){
    CCLOG("The restart button for the game lose screen has been clicked and this is the result");
    this->loseScreen->hide();
    this->levelRestart();
}

void CRLevel::loseScreenHomeButtonSelected(){
    CCLOG("The home button for the game lose screen has been clicked and this is the result");
    
    auto newScene = MenuMap::create();
    Director *currentDirector = Director::getInstance();
    
    if (currentDirector->getRunningScene())
    {
        TransitionFade *transition = TransitionFade::create(0.3, newScene);
        currentDirector->replaceScene(transition);
    }
    else
    {
        currentDirector->runWithScene(newScene);
    }
}


void CRLevel::tutorialScreenStartButtonSelected(){
    CCLOG("The button restart for the tutorial screen has been clicked and this is the result");
    this->levelStart();
}



void CRLevel::tutorialScreenHomeButtonSelected(){
    CCLOG("The home button for the tutorial screen has been clicked and this is the result");
    auto newScene = MenuMap::create();
    Director *currentDirector = Director::getInstance();
    
    if (currentDirector->getRunningScene())
    {
        TransitionFade *transition = TransitionFade::create(0.3, newScene);
        currentDirector->replaceScene(transition);
    }
    else
    {
        currentDirector->runWithScene(newScene);
    }

}



// helper methods

float CRLevel::randomFloat(float min, float max)
{
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = max - min;
    float r = random * diff;
    return min + r;
}


Rect CRLevel::fullBoundingBox(Node *target)
{
    Vector<Node*> stack(target->getChildrenCount());
    float leftmost = target->getBoundingBox().origin.x;
    float rightmost = leftmost + target->getBoundingBox().size.width;
    float lowest = target->getBoundingBox().origin.y;
    float highest = lowest + target->getBoundingBox().size.height;
    Vector<Node*> children = target->getChildren();
    for (Node *child: children) {
        stack.pushBack(child);
    }
    while (stack.size() > 0)
    {
        Node *node = stack.back();
        stack.popBack();
        Rect bb = CRLevel::boundingBoxConvertedToNodeSpace(target, node);
        float nodeleftmost = bb.origin.x;
        float noderightmost = bb.origin.x + bb.size.width;
        float nodelowest = bb.origin.y;
        float nodehighest = bb.origin.y + bb.size.height;
        leftmost = fmin(leftmost,nodeleftmost);
        rightmost = fmax(rightmost,noderightmost);
        lowest = fmin(lowest,nodelowest);
        highest = fmax(highest,nodehighest);
        for (Node *child: node->getChildren()) {
            stack.pushBack(child);
        }
    }
    float width = rightmost - leftmost;
    float height = highest - lowest;
    return Rect(leftmost,lowest,width,height);
}

Rect CRLevel::boundingBoxConvertedToNodeSpace(Node *target, Node *other)
{
    // Get the bottomLeft and topRight corners of the other node's bounding box
    // in the other node's coordinate space.
    Rect boundingBox = other->getBoundingBox();
    Vec2 bottomLeft = Vec2(boundingBox.origin.x, boundingBox.origin.y);
    Vec2 topRight = Vec2(boundingBox.origin.x + boundingBox.size.width, boundingBox.origin.y + boundingBox.size.height);
    
    // Convert bottomLeft and topRight to the global coordinate space.
    Vec2 worldSpaceBottomLeft = other->getParent()->convertToWorldSpace(bottomLeft);
    Vec2 worldSpaceTopRight = other->getParent()->convertToWorldSpace(topRight);
    
    // Convert worldSpaceBottomLeft and worldSpaceTopRight into this node's
    // local coordinate space.
    Vec2 nodeSpaceBottomLeft = worldSpaceBottomLeft;
    Vec2 nodeSpaceTopRight = worldSpaceTopRight;
    if (target->getParent()) {
        nodeSpaceBottomLeft = target->getParent()->convertToNodeSpace(worldSpaceBottomLeft);
        nodeSpaceTopRight = target->getParent()->convertToNodeSpace(worldSpaceTopRight);
    }
    
    // Finally, construct the bounding box in this node's local coordinate space
    // and return it.
    float width = nodeSpaceTopRight.x - nodeSpaceBottomLeft.x;
    float height = nodeSpaceTopRight.y - nodeSpaceBottomLeft.y;
    return Rect(nodeSpaceBottomLeft.x, nodeSpaceBottomLeft.y, width, height);
}
