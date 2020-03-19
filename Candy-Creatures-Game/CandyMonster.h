//
//  CandyMonster.hpp
//  CandyCreatures
//
//  Created by moeezo saleem on 12/17/15.
//
//

#ifndef CandyMonster_hpp
#define CandyMonster_hpp

#include <stdio.h>

USING_NS_CC;


class CandyMonster : public cocos2d::Sprite
{
private:
    
    virtual void initialize();
    virtual void onExit();
    
    
public:
    
    float speedVerticle;
    float speedHorizontal;
    
    float prevSpeedHorizontal;
    
    float moveByActionDuration;
    float collisionOffset;
    float collisionOffsetYbottom;
    float collisionOffsetYtop;
    // state variables to alter the animations
    bool isOutside;
    float timeOutside;
    bool hasWon;
    bool isHit;
    bool shouldWalkStraight;
    bool shouldCatchPlayer;
    int hitCount;
    static CandyMonster * create();
    Sprite * bgSprite;
    void update(float dt);
    void upAndDownMotion();
    void hitAnimation();
    void forwardMotion();
    void checkRightWall();
    void checkLeftWall();
    void checkTopWall();
    void checkBottomWall();
    
    void restoreSpeedHorizontal(float dt);
};


#endif /* CandyMonster_hpp */
