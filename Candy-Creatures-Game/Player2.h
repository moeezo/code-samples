//
//  Player2.hpp
//  CandyCreatures
//
//  Created by moeezo saleem on 12/23/15.
//
//

#ifndef Player2_hpp
#define Player2_hpp


#include "cocos2d.h"
#include <stdio.h>



using namespace cocos2d;



class Player2 : public cocos2d::Sprite
{
private:
    
    virtual void initialize();
    virtual void onExit();
    
    
public:
    
    
    
    static Player2 * create();
    Sprite * bgSprite;
    bool hasThrown;    //play throw animation if its true
    void update(float dt);
    void animatePlayerWalk();
    void stopAnimatePlayerWalk();
    void animatePlayerBackground();
    
    
};

#endif /* Player2_hpp */
