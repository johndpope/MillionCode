#ifndef __MillionCode__FoodNumberData__
#define __MillionCode__FoodNumberData__

#include <cocos2d.h>
#include <iostream>
#include "Generic.h"
#include "DataKey.h"


class FoodNumberData
{
public:

    static void SaveData(int foodNumber, int count);
    static int LodeData(int foodNumber);
private:
};

#endif /* defined(__MillionCode__FoodNumberData__) */
