//
//  CRLevelData.hpp
//  CandyCreatures
//
//  Created by moeezo saleem on 12/17/15.
//
//

#ifndef CRLevelData_hpp
#define CRLevelData_hpp

#include <stdio.h>


class CRLevelData
{
public:

    
    CRLevelData(int levelId, bool isLocked, float bestTime);
    
    /*! This can be changed, so it's public. */
    bool isLocked;
    
    
    // accessor functions because these values should only be read
    int getLevelId();
    float getBestTime();
    
private:
    
    int levelId;
    
    float bestTime;
    
};



#endif /* CRLevelData_hpp */
