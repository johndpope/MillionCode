#include "FoodCreate.h"
#include "MenuScene.h"
#include "EatScene.h"
#include "LinkJava.h"
#include "DataKey.h"
#include "MonsterEqData.h"

using namespace cocos2d;
using namespace std;

const string BaseKey = "FoodDataKey";
const string ImgPath = "img/fruit/";
const string LineURL = "http://line.me/ti/p/";

static const float ActionTime = 2.0f;

enum ImgTag
{
    e_BG,
    e_Food,
    e_TapFont,
    e_Num
};

Scene* FoodCreate::createScene()
{
    Scene *scene = Scene::create();
    FoodCreate *layer = FoodCreate::create();
    scene->addChild(layer);
    return scene;
}


// on "init" you need to initialize your instance
bool FoodCreate::init()
{
    if ( !CCLayer::init() ) { return false; }
    
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    LinkJava::JavaEvent();
#endif
    
    m_VisibleSize = Director::getInstance()->getVisibleSize();
    m_Mag = Generic::getScreenMagnification(m_VisibleSize);
    m_IsActiv = false;
    m_IsMakeEnd = false;
    //LoadFoodData::loadName("foodName", "text/");

    //auto seedStr = String::create(UserDefault::getInstance()->getStringForKey("SeedString"));
    //this->setSeed(seedStr->getCString());
    
    this->scheduleUpdate();
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(FoodCreate::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(FoodCreate::onTouchEnded, this);
    
    auto dip = Director::getInstance()->getEventDispatcher();
    dip->addEventListenerWithSceneGraphPriority(listener, this);

	UserDefault* def = UserDefault::getInstance();
	def->setIntegerForKey(SaveDataKey[n_DataKeyNum::eMonsterData01].c_str(), n_MonsterData::eMonster4);
	def->flush();
	
	this->sprite();
    return true;
}

void FoodCreate::update(float delta)
{
}


void FoodCreate::make()
{
	/*
    CCLOG("つくるおー");
    int num = 0;
    int total = UserDefault::getInstance()->getIntegerForKey(SaveDataKey[n_DataKeyNum::eFoodTotal].c_str());
    CCLOG("total:%d", total);
    string seed = CCUserDefault::getInstance()->getStringForKey("SeedString");
    CCLOG("atio:%d", atoi(seed.c_str()));
    UserDefault::getInstance()->setStringForKey("SeedString", "NULL");
    UserDefault::getInstance()->flush();
    int len = FoodCreate::countBit(seed.c_str());
    int tmSeed;
    
    if(atoi(seed.c_str()) != 0)
    {
        srand(atoi(seed.c_str()));
        num = rand() % total + 1;
    }
    
    else if(seed.find(LineURL) != string::npos)
    {
        const char *s = seed.c_str();
        int i = 0;
        for(int ii = 0; ii < len; ii ++)
        {
            i += s[ii];
        }
        CCLOG("line:%d", i);
        srand(i);
        num = rand() % total + 1;
    }
    
    else
    {
        srand(len);
        tmSeed = rand() % len;
        for(int ii = 0; ii < 3; ii ++)
            tmSeed += rand() % 10;
        srand(tmSeed);
        num = rand() % total + 1;
    }
    
    
    if(num <= total)
    {
        string Num = Generic::intToStrnig(num);
        string key = BaseKey + Num;
        CCLOG("key:%s", key.c_str());
        
        
        string name = UserDefault::getInstance()->getStringForKey(key.c_str());
        CCLOG("name:%s", name.c_str());
        
        
        string path = ImgPath + name.c_str() + ".png";
        CCLOG("path:%s",path.c_str());
        
 
        auto Food = Sprite::create(path.c_str());
        Food->setScale(0);
        Food->setPosition(Vec2(m_VisibleSize.width/2, m_VisibleSize.height*2/5));
        this->addChild(Food, ImgTag::e_Food);
        ActionInterval *action = CCScaleTo::create(ActionTime, 1.0f*m_Mag);
        ActionInterval *fadein = CCFadeIn::create(ActionTime);
        ActionInterval* jumpAction = CCJumpTo::create(ActionTime, Vec2(m_VisibleSize.width/2, m_VisibleSize.height*2/5), 200*m_Mag, 1);
        Food->runAction(CCSequence::create(action, fadein, jumpAction, NULL));
    }
    else {
        CCLOG("その番号は存在しません");
    }
	*/
}

void FoodCreate::sprite()
{
	//CCLOG("すぷらいとーおん！");
    auto bg = Sprite::create("img/BG/menu.png");
    bg->setScale(m_Mag);
    bg->setPosition(Vec2(m_VisibleSize.width/2, m_VisibleSize.height/2));
    this->addChild(bg, ImgTag::e_BG);
    CCLOG("bg\nx:%d y:%d", (int)bg->getPositionX(), (int)bg->getPositionY());
    
    //m_TapFont = CCSprite::create("Img/tap.png");
    //m_TapFont->setPosition(ccp(m_VisibleSize.width/2, m_VisibleSize.height/2));
    //m_TapFont->setScale(m_Mag);
    //m_TapFont->setOpacity(0);
    //this->addChild(m_TapFont, n_MC::e_TapFont);
    //CCActionInterval *fadein = CCFadeIn::create(2.0f);
    //CCActionInterval *fadeout = CCFadeOut::create(1.0f);
    //CCSpawn *spawn = CCSpawn::create(fadein, fadeout);
    //CCRepeatForever *repeatForever = CCRepeatForever::create(spawn);
    //m_TapFont->runAction(repeatForever);
}


bool FoodCreate::onTouchBegan(Touch* pTouch, Event* pEvent)
{
    return true;
}


void FoodCreate::onTouchEnded(Touch* pTouch, Event* pEvent)
{
    CCLOG("たっちえんどかいしー");
    if(m_IsMakeEnd == true)
    {
        Scene *next = EatScene::createScene();
        Scene *pScene = TransitionCrossFade::create(1.0f, next);
        Director::getInstance()->replaceScene(pScene);
    }
    else if(UserDefault::getInstance()->getBoolForKey("IsSeedGet"))
    {
		//CCLOG("いずしーどげっと？");
        UserDefault::getInstance()->setBoolForKey("IsSeedGet", false);
        m_IsMakeEnd = true;
        m_IsActiv = true;
        //m_TapFont->setVisible(false);
        CCLOG("めいくにいどうー");
        this->make();
    }
}


void FoodCreate::setSeed(const char* seedData)
{
    CCLOG("せっとしーど");
    int len = 0;
    CCLOG("%s",seedData);
    len = countBit(seedData);
    int tmSeed = 0;
    srand(len);
    for(int ii = 0; ii < 3; ii ++)
        tmSeed += rand() % 10;
    srand(tmSeed);
    int seed = 0;
    seed = rand() % CCUserDefault::getInstance()->getIntegerForKey(SaveDataKey[8].c_str()) + 1;
    UserDefault::getInstance()->setIntegerForKey("Seed", seed);
    UserDefault::getInstance()->setBoolForKey("IsSeedGet", true);
    CCLOG("せっとしーどおわりー");
    CCUserDefault::getInstance()->flush();
}


int FoodCreate::countBit(const char* data)
{
    string st = data;;
    CCLOG("byte:%lu", st.length());
    return st.length();
}
