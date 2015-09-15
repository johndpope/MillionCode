#include "Monster.h"

using namespace cocos2d;
using namespace std;

static const string ImgPath = "img/monster/";

static const char* monsFro[] = {
    "/front_stand.png",
    "/front_damage.png",
    "/front_attack00.png",
    "/front_attack01.png",
};

static const char* monsBack[] = {
    "/back_stand.png",
    "/back_damage.png",
    "/back_attack00.png",
    "/back_attack01.png",
};

bool Monster::initWithFile(const char* fileName, int num)
{
    string fname = ImgPath + fileName + monsFro[num];
    m_Sprite = Sprite::create(fname.c_str());
    return true;
}

bool Monster::initWithPlayer(const char *fileName, int num)
{
    string fname = ImgPath + fileName + monsBack[num];
    m_Sprite = Sprite::create(fname.c_str());
    return true;
}

Monster* Monster::create(const char* fileName, int num)
{
    Monster* monster = new Monster();
    if(monster && monster->initWithFile(fileName, num))
    {
        monster->autorelease();
        monster->retain();
        return monster;
    }
    CC_SAFE_DELETE(monster);
    return NULL;
}

Monster* Monster::createPlayer(const char* fileName, int num)
{
    Monster* monster = new Monster();
    if(monster && monster->initWithPlayer(fileName, num))
    {
        monster->autorelease();
        monster->retain();
        return monster;
    }
    CC_SAFE_DELETE(monster);
    return NULL;
}

Monster* Monster::createEnemy(const char *race)
{
    ST st = MonsterData::loadMonsterData(race, "data/MonsterData/");
    
    return NULL;
}

void Monster::addScene(Node* scene){
    if (m_Sprite != NULL) scene->addChild(m_Sprite);
}

void Monster::addScene(Node* scene, int tag)
{
    if (m_Sprite != NULL) scene->addChild(m_Sprite, tag);
}

void Monster::addScene(Node* scene, int zOrder, int tag)
{
    if (m_Sprite != NULL) scene->addChild(m_Sprite, zOrder, tag);
}

void Monster::setTexture(const char *fileName, int num)
{
    string path = ImgPath + fileName + monsFro[num];
    m_Sprite->setTexture(Director::getInstance()->getTextureCache()->addImage(path.c_str()));
}

void Monster::setPlayerTexture(const char *fileName, int num)
{
    string path = ImgPath + fileName + monsBack[num];
    m_Sprite->setTexture(Director::getInstance()->getTextureCache()->addImage(path.c_str()));
}

void Monster::setPosition(const Point &pos)
{
    m_Sprite->setPosition(pos);
}

Point Monster::getPos()
{
    return m_Sprite->getPosition();
}

Size Monster::getContentSize()
{
    return m_Sprite->getContentSize();
}

void Monster::setScale(float fScale)
{
    m_Sprite->setScale(fScale);
}

void Monster::setScaleX(float fScaleX)
{
    m_Sprite->setScaleX(fScaleX);
}

void Monster::setScaleY(float fScaleY)
{
    m_Sprite->setScaleY(fScaleY);
}