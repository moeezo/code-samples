//
//  CRSingleton.cpp
//  CandyCreatures
//
//  Created by moeezo saleem on 12/17/15.
//
//

#include "CRSingleton.h"


CRSingleton *CRSingleton::getInstance()
{
    static CRSingleton *instance = nullptr;
    
    if (instance == nullptr)
    {
        instance = new CRSingleton();
    }
    
    return instance;
    
}


CRSingleton::CRSingleton()
{
    //initialize the singleton with default values at startup
    
    currentLevelId = 0;
    
    // create each level data and add to vector
    
    // level 0
    addLevelData(0,
                 false,
                 1000);
    
    addLevelData(1,
                 true,
                 1000);
}

CRSingleton::~CRSingleton()
{
    for( auto &data : levelDataVector )
    {
        delete data;
    }
}


void CRSingleton::setCurrentLevelId(int pLevelId)
{
    int result = -1;
    int index = 0;
    for(auto &data : levelDataVector )
    {
        if( data->getLevelId() == pLevelId )
        {
            result = index;
            break;
        }
        
        index++;
    }
    
    CCASSERT(result >= 0 , "Couldn't find level ID in setCurrentLevelId");
    currentLevelId = result;
}


CRLevelData* CRSingleton::getCurrentLevelData()
{
    //CCLOG("level id: %i", levelDataVector.at(currentLevelIndex)->getLevelId());
    return levelDataVector.at(currentLevelId);
}

CRLevelData* CRSingleton::getLevelDataWithId(int pLevelId)
{
    CRLevelData* result = nullptr;
    for( auto &data : levelDataVector )
    {
        if( data->getLevelId() == pLevelId )
        {
            result = data;
        }
    }
    return result;
}

void CRSingleton::unlockNextLevelWithCurrentLevelId(int pLevelId)
{
    int result = -1;
    int matchingIndex = -1;
    int index = 0;
    for( auto &data : levelDataVector )
    {
        if( data->getLevelId() == pLevelId )
        {
            matchingIndex = index;
        }
        else if( matchingIndex >= 0 )
        {
            // next one
            result = data->getLevelId();
            break;
        }
        
        index++;
    }
    
    int nextLevelId = result;
    
    if( nextLevelId >= 0 )
    {
        const char * key = CRSingleton::getKeyForLevelLocked(nextLevelId);
        
        UserDefault::getInstance()->setBoolForKey(key, false);
        UserDefault::getInstance()->flush();
    }

}

void CRSingleton::addLevelData(int pLevelId, bool pisLocked, float pbestTime)

{
    CRLevelData *data = new CRLevelData(pLevelId, pisLocked, pbestTime);
    levelDataVector.push_back(data);
    
}

const char * CRSingleton::createKeyWithStringAndNumber(string key, int number)
{
    string newkey = key + to_string(number);
    
    char * writable = new char[newkey.size() + 1];
    copy(newkey.begin(), newkey.end(), writable);
    writable[newkey.size()] = '\0'; // don't forget the terminating 0
    
    return writable;
}

const char * CRSingleton::getKeyForLevelLocked(int plevelId)
{
    return CRSingleton::createKeyWithStringAndNumber(KEY_LEVEL_LOCKED, plevelId);
}

const char * CRSingleton::getKeyForLevelBestTime(int plevelId)
{
    return CRSingleton::createKeyWithStringAndNumber(KEY_LEVEL_BEST_TIME, plevelId);
}


void CRSingleton::updateLivesCount(int count)
{
    UserDefault::getInstance()->setIntegerForKey(KEY_LIVES_COUNT, count);
    UserDefault::getInstance()->flush();
}

void CRSingleton::updateLastLifeTime( int lifeTime)
{
    UserDefault::getInstance()->setIntegerForKey(KEY_LAST_LIFE_TIME, lifeTime);
    UserDefault::getInstance()->flush();
}


//////public static storage functions///////

void CRSingleton::initialize(){
    
    UserDefault::getInstance()->setBoolForKey(STORAGE_KEY_SETUP_DONE, true);
    
    CRSingleton::updateLivesCount(3);
    CRSingleton::updateLastLifeTime(0);
   
    
    for ( auto &data : CRSingleton::getInstance()->levelDataVector )
    {
        const char * key = CRSingleton::getKeyForLevelLocked(data->getLevelId());
        UserDefault::getInstance()->setBoolForKey(key, data->isLocked);
        UserDefault::getInstance()->flush();
    }
    
  

}

int CRSingleton::getLivesCount(){
    return UserDefault::getInstance()->getIntegerForKey(KEY_LIVES_COUNT);
}


int CRSingleton::getLastLifeTime(){
    return UserDefault::getInstance()->getIntegerForKey(KEY_LAST_LIFE_TIME);
}


int CRSingleton::getBestTimeForLevel(int levelId){
    const char * key = CRSingleton::getKeyForLevelBestTime(levelId);
    return UserDefault::getInstance()->getIntegerForKey(key);
}

bool CRSingleton::getIsLockedForLevel(int levelId){
    const char * key = CRSingleton::getKeyForLevelLocked(levelId);
    return UserDefault::getInstance()->getIntegerForKey(key);
}


void CRSingleton::updateBestTimeForLevel(int time, int levelId){
    int currentTime = CRSingleton::getBestTimeForLevel(levelId);
    if (currentTime > time)
    {
        const char * key = CRSingleton::getKeyForLevelBestTime(levelId);
        UserDefault::getInstance()->setIntegerForKey(key, time);
        UserDefault::getInstance()->flush();
    }
}

void CRSingleton::setLastLifeTime(int time){
    CRSingleton::updateLastLifeTime(time);
}

void CRSingleton::setLivesCount(int count){
    CRSingleton::updateLivesCount(count);
}
