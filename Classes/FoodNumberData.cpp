#include "FoodNumberData.h"

using namespace cocos2d;
using namespace std;

void FoodNumberData::SaveData(int foodNumber, int count)
{
	/*
    string saveKey = SaveDataKey[n_DataKeyNum::eFoodNumber] + Generic::intToStrnig(foodNumber);
    UserDefault::getInstance()->setIntegerForKey(saveKey.c_str(), count);
    UserDefault::getInstance()->flush();
	*/
}

int FoodNumberData::LodeData(int foodNumber)
{
	/*
    string dataKey = SaveDataKey[n_DataKeyNum::eFoodNumber] + Generic::intToStrnig(foodNumber);
    int count = UserDefault::getInstance()->getIntegerForKey(dataKey.c_str(), 0);
    return count;
	*/
	return 0;
}