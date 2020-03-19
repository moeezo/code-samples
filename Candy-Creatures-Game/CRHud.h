//
//  CRHud.hpp
//  CandyCreatures
//
//  Created by moeezo saleem on 12/19/15.
//
//

#ifndef CRHud_hpp
#define CRHud_hpp

#include <stdio.h>


USING_NS_CC;

class CRHudDelegate
{
public:
    virtual void CRHudPauseButtonSelected();
};


class CRHud : public Sprite
{
private:
    
    float paddingH;
    float paddingV;
    
    Sprite* overlayBar;
    
    Sprite *viwAllLives;

    float labelHeight;
    
    CRHudDelegate *delegate;
    
    void initialize();
    
    void setupTimerView();
    void refreshNumberOfLives();
    void resetTimer();

    void update(float dt);
    void updateTimer(float dt);
    
    std::string getTimeString(int seconds);
    std::string getTimeStringFromMilliSeconds(float milliSeconds);
    
    static CRHud * create();
    
    virtual void onExit();
    
   
    
public:
    
    float numSeconds;
    
    Label *livesCountLabel;
    Label *lblTimer;
    Label *lblTitle;
    
    void startTime();
    void pauseTime();
    void resumeTime();
    void stopTime();
    void hideOverlay();
    
    void resetHud();
  
    
    static CRHud * getInstance(CRHudDelegate *delegate);
    
    void setDelegate(CRHudDelegate *delegate);
    
};






#endif /* CRHud_hpp */


