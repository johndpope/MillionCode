#ifndef __MillionCode__Generic__
#define __MillionCode__Generic__

#include <string>
#include <iostream>
#include <cocos2d.h>

using std::string;


typedef struct StatusBase
{
    int hp;
    int atk;
    int dfe;
    int dex;
}STB;

typedef struct Status
{
    std::string race;
    std::string name;
    int lv;
    int exp;
    int stuff;
    STB st;
    STB gf;
    STB effort;
    int evoLv;
    int criteria;
    std::string evoNega;
    std::string evoPosi;
    std::string evo;
}ST;

class Generic
{
public:
    static std::string intToStrnig(int i);
    static float getScreenMagnification(cocos2d::Size size);
    static void setSeed(const char* seedData);
	static bool checkSaveData();
	static void shake(cocos2d::Node* node);
};

#endif /* defined(__MillionCode__Generic__) */
