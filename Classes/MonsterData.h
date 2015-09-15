#ifndef __MillionCode__MonsterData__
#define __MillionCode__MonsterData__

#include <iostream>
#include <cocos2d.h>
#include "Generic.h"

class MonsterData
{
public:
    static ST loadMonsterData(std::string monster, std::string folderpath);
    static ST monsterSaveDataAnalysis(std::string key);
    static int monsterAnalysisInt(std::string keyword, std::string data);
    static std::string monsterAnalysisString(std::string keyword, std::string data);
    static void saveMonsterData(ST st, std::string key);
};
#endif /* defined(__MillionCode__MonsterData__) */
