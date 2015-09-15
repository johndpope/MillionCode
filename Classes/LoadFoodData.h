#ifndef __MillionCode__LoadFoodData__
#define __MillionCode__LoadFoodData__

#include <cocos2d.h>
#include <iostream>
#include "DataKey.h"

typedef struct foodStatus
{
    int hp;
    int atk;
    int def;
    int dex;
    int eva;
    
}FST;

class LoadFoodData
{
public:
    static void loadName(std::string fname, std::string folderPath);
    static FST foodStatus(std::string fname, std::string folderPath);
private:
    
    static int foodAnalysis(std::string keyword, std::string data);
    static std::string saveNameKey;
};

#endif /* defined(__MillionCode__LoadFoodData__) */
