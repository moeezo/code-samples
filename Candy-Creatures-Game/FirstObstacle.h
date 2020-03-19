//
//  FirstObstacle.hpp
//  CandyCreatures
//
//  Created by moeezo saleem on 12/18/15.
//
//

#ifndef FirstObstacle_hpp
#define FirstObstacle_hpp

#include <stdio.h>


using namespace cocos2d;



class FirstObstacle : public cocos2d::Sprite
{
private:
    
    virtual void initialize();
    virtual void onExit();
    
public:
    
    
    
    static FirstObstacle * createWithType(int obType);
    int obstacleType;
    Sprite * bgSprite;
    bool hasMoveEnded;
    void update(float dt);
    void moveObstacle();
    void animateFullRotation();
    void animateBackNForth();
    void animateScaling();
    void animateStrawberry();
   
    
    
};


#endif /* FirstObstacle_hpp */
