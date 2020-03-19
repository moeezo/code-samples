//
//  CRLevelData.cpp
//  CandyCreatures
//
//  Created by moeezo saleem on 12/17/15.
//
//

#include "CRLevelData.h"


CRLevelData::CRLevelData(int vlevelId, bool visLocked, float vbestTime){
    this->levelId = vlevelId;
    this->isLocked = visLocked;
    this->bestTime = vbestTime;
    
}


int CRLevelData::getLevelId(){
    return levelId;
}

float CRLevelData::getBestTime(){
    return bestTime;
}