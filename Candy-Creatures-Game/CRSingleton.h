//
//  CRSingleton.hpp
//  CandyCreatures
//
//  Created by moeezo saleem on 12/17/15.
//
//

#ifndef CRSingleton_hpp
#define CRSingleton_hpp


#define STORAGE_KEY_SETUP_DONE  "SetupDone"
#define KEY_LEVEL_LOCKED        "LevelLocked"
#define KEY_LEVEL_BEST_TIME     "LevelBestTime"
#define KEY_LIVES_COUNT         "LivesCount"
#define KEY_LAST_LIFE_TIME      "LastLifeCount"



#include <stdio.h>
#include "CRLevelData.h"


USING_NS_CC;
using namespace std;


class CRSingleton
{
private:
    
    CRSingleton();
    ~CRSingleton();
    
    int currentLevelId;
    int livesCount;
    int timeLastLife;
    
    static const char * createKeyWithStringAndNumber(string key, int number);
    static const char* getKeyForLevelLocked(int plevelId);
    static const char* getKeyForLevelBestTime(int plevelId);
    static void updateLivesCount(int count);
    static void updateLastLifeTime( int LifeTime);
public:
    
    static CRSingleton * getInstance();
    
    std::vector<CRLevelData*> levelDataVector;
    
    void setCurrentLevelId(int pLevelId);

    CRLevelData* getCurrentLevelData();
    CRLevelData* getLevelDataWithId(int pLevelId);
    
    void unlockNextLevelWithCurrentLevelId(int currentLevelId);
    
    void addLevelData(int pLevelId, bool pisLocked, float pbestTime);
    
    
    static void initialize();
    static int getLivesCount();
    static int getLastLifeTime();
    
    static void setLastLifeTime(int time);
    static void setLivesCount(int count);
    
    static int getBestTimeForLevel(int levelId);
    static bool getIsLockedForLevel(int levelId);
    
    static void updateBestTimeForLevel(int time, int levelId);
    
    
};





#endif /* CRSingleton_hpp */
