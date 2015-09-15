#include "Generic.h"
#include "MonsterEqData.h"
#include "DataKey.h"

using namespace cocos2d;
using namespace std;

static const int DefaultH = 720;
//static const int DefaultW = 1280;

string Generic::intToStrnig(int i)
{
    string st = "";
    char tmChar[128];
    sprintf(tmChar, "%d", i);
    st += tmChar;
    return st;
}

float Generic::getScreenMagnification(Size size)
{
    float mag;
    mag = size.height / DefaultH;
    return mag;
}

void Generic::setSeed(const char* seedData)
{
    UserDefault* userDef = UserDefault::getInstance();
    userDef->setStringForKey("SeedString", seedData);
    userDef->setBoolForKey("IsSeedGet", true);
    userDef->flush();
}

bool Generic::checkSaveData()
{
	bool dataAvailable;
	UserDefault* def = UserDefault::getInstance();
	int monsterData;
	monsterData = def->getIntegerForKey(SaveDataKey[n_DataKeyNum::eMonsterData01].c_str());
	if (monsterData == n_MonsterData::eEmpty)
	{
		dataAvailable = false;
	}
	else
	{
		dataAvailable = true;
	}

	return dataAvailable;
}

void Generic::shake(cocos2d::Node* node)
{
	float x, y;
	x = node->getPositionX();
	y = node->getPositionY();
	auto pos1 = MoveTo::create(0.05f, Vec2(x + 10, y - 10));
	auto pos2 = MoveTo::create(0.05f, Vec2(x - 5, y - 7));
	auto pos3 = MoveTo::create(0.05f, Vec2(x + 7, y + 4));
	auto pos4 = MoveTo::create(0.05f, Vec2(x + 10, y + 10));
	auto pos5 = MoveTo::create(0.05f, Vec2(x - 8, y - 5));
	auto pos6 = MoveTo::create(0.05f, Vec2(x - 15, y + 12));
	auto pos7 = MoveTo::create(0.05f, Vec2(x + 3, y - 8));
	auto pos8 = MoveTo::create(0.05f, Vec2(x - 4, y + 10));
	auto pos9 = MoveTo::create(0.05f, Vec2(x, y));

	node->runAction(Sequence::create(pos1, pos2, pos3, pos4, pos5, pos6, pos7, pos8, pos9, NULL));
}