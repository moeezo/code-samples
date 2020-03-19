//
//  Player.hpp
//  CandyCreatures
//
//  Created by moeezo saleem on 12/14/15.
//
//

#ifndef Player_hpp
#define Player_hpp


#include "cocos2d.h"
#include <stdio.h>



using namespace cocos2d;



class Player : public cocos2d::Sprite
{
private:
    
    virtual void initialize();
    virtual void onExit();
    
    
public:
    

    
    static Player * create();
    Sprite * bgSprite;
    bool hasThrown;    //play throw animation if its true
    void update(float dt);
    void animatePlayerWalk();
    void stopAnimatePlayerWalk();
    void animatePlayerBackground();
    
   
};






#endif /* Player_hpp */
