//
//  Level1Background.hpp
//  CandyCreatures
//
//  Created by moeezo saleem on 12/17/15.
//
//

#ifndef Level1Background_hpp
#define Level1Background_hpp

#include <stdio.h>

USING_NS_CC;


class Level1Background : public cocos2d::Sprite
{
private:
    
    virtual void initialize();
    virtual void onExit();
    
    
public:
    
    
 
    static Level1Background * create();
    Sprite * bgSprite1;
    Sprite * bgSprite2;
    void update(float dt);
  
    
};

#endif /* Level1Background_hpp */
