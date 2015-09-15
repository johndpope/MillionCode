#include "MonsterCreate.h"
#include "MenuScene.h"
#include "LinkJava.h"
#include "MonsterEqData.h"


using namespace cocos2d;
using namespace std;

static const float ActionTime = 2.0f;

const int TOTAL_INIT_MONSTER_NUM = 6;
const string LineURL = "http://line.me/ti/p/";

enum imgTag
{
    e_BG,
    e_Monster,
    e_TapFont,
    e_Num
};

Scene* MonsterCreate::createScene() {
    auto scene = Scene::create();
    auto layer = MonsterCreate::create();
    scene->addChild(layer);
    return scene;
}

bool MonsterCreate::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

	//init values
	seedStr = "";
	m_IsActiv = false;
	m_IsMakeEnd = false;
	m_slot = 0;
	m_confirm = nullptr;

	m_VisibleSize = CCDirector::getInstance()->getVisibleSize();
	m_Mag = Generic::getScreenMagnification(m_VisibleSize);

	//bg
	this->sprite();
	
	slotSelection();
    
    return true;
}

void MonsterCreate::update(float delta)
{
}

void MonsterCreate::cameraProcess(cocos2d::Ref *pSender, int slot)
{
	
	this->removeChild(instructions);
	this->removeChild(selectionMenu);
	this->removeChild(m_rtnBtn);

	m_slot = slot;
	//error case sets monster to dummy monster.
	UserDefault::getInstance()->setIntegerForKey(SaveDataKey[(n_DataKeyNum::eMonsterData01) + m_slot].c_str(), 0);

	tmpWaiter = Sprite::create();
	this->addChild(tmpWaiter);

	auto startConfirm = CallFunc::create([this](){this->confirmation(STARTING); });
	auto camera = CallFunc::create([this](){this->runCamera(); });
	auto data = CallFunc::create([this](){this->getData(); });
	auto endConfirm = CallFunc::create([this](){this->confirmation(ENDING); });
	auto enableEnd = CallFunc::create([this](){this->eventHandler(); });
	auto enableCreation = CallFunc::create([this](){this->make(); });
	auto waitS = FadeOut::create(2.0f);
	auto waitL = FadeOut::create(3.0f);

	tmpWaiter->runAction(Sequence::create(startConfirm, waitL, camera, waitS, endConfirm, waitL, data, enableCreation, enableEnd, NULL));
}

void MonsterCreate::slotSelection()
{
	//back button
	string btn = "img/UI/menu/UI_M_009.png";
	string pushBtn = "img/UI/menu/UI_M_010.png";

	auto btnItem = MenuItemImage::create(btn.c_str(),
		pushBtn.c_str(),
		CC_CALLBACK_1(MonsterCreate::menuReturn, this));
	btnItem->setScale(m_Mag * 0.85);
	m_rtnBtn = Menu::create(btnItem, NULL);
	m_rtnBtn->setPosition(Vec2(m_VisibleSize.width - btnItem->getContentSize().width / 2,
		btnItem->getContentSize().height / 2));
	this->addChild(m_rtnBtn);


	//load monsters and create selector(menu, menuItems)
	auto fileU = FileUtils::getInstance();
	auto fileContent = fileU->getStringFromFile("data/animData.xml");
	UserDefault* def = UserDefault::getInstance();
	doc.Parse(fileContent.c_str());

	instructions = Label::createWithTTF("どのモンスターを消しますか", "fonts/ant-maru.ttf", 60);
	instructions->enableOutline(Color4B::BLACK, 2);
	instructions->setPosition(Vec2(m_VisibleSize.width / 2, m_VisibleSize.height / 1.2f));
	this->addChild(instructions);

	MenuItemImage* monsterItem[3];

	for (int i = 0; i < 3; i++)
	{
		auto monsterName = def->getIntegerForKey(SaveDataKey[n_DataKeyNum::eMonsterData01 + i].c_str());
		auto monsterPath = doc.FirstChildElement()->FirstChildElement(MonsterNameData[monsterName].c_str())->FirstChildElement("spriteList")->FirstChildElement("animation")->FirstChildElement("stand")->GetText();
		monsterItem[i] = MenuItemImage::create(monsterPath, monsterPath, CC_CALLBACK_1(MonsterCreate::cameraProcess, this, i));
		monsterItem[i]->setPositionX(m_VisibleSize.width / (i + 1));
		switch (i)
		{
		case 0:
			monsterItem[i]->setPosition(Vec2(m_VisibleSize.width/ 6, m_VisibleSize.height / 2));
			break;
		case 1:
			monsterItem[i]->setPosition(Vec2((m_VisibleSize.width * 3) / 6, m_VisibleSize.height / 2));
			break;
		case 2:
			monsterItem[i]->setPosition(Vec2((m_VisibleSize.width * 5) / 6, m_VisibleSize.height / 2));
			break;
		default:
			break;
		}

		monsterItem[i]->setScale(m_Mag * 0.7f);
	}
	
	selectionMenu = Menu::create(monsterItem[0], monsterItem[1], monsterItem[2], NULL);
	selectionMenu->setPosition(Point::ZERO);
	this->addChild(selectionMenu);
}

void MonsterCreate::menuReturn(cocos2d::Ref* pSender)
{
	auto nextScene = MenuScene::createScene();
	auto pScene = TransitionFade::create(0.5f, nextScene);
	Director::getInstance()->replaceScene(pScene);
}

void MonsterCreate::eventHandler()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(MonsterCreate::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(MonsterCreate::onTouchEnded, this);

	auto dip = Director::getInstance()->getEventDispatcher();
	dip->addEventListenerWithSceneGraphPriority(listener, this);
}

void MonsterCreate::confirmation(int confirmCase)
{
	if (confirmCase == STARTING)
	{
		m_confirm = Sprite::create("img/UI/result/UI_W_008.png");
	}
	else if (confirmCase == ENDING)
	{
		m_confirm = Sprite::create("img/UI/result/UI_W_009.png");
	}
	
	m_confirm->setPosition(m_VisibleSize.width / 2, -300);
	m_confirm->setTextureRect(Rect(0, 0, 400, 300));
	m_confirm->setScale(m_Mag);

	this->addChild(m_confirm);

	auto moveConfirm = MoveTo::create(0.6f, Vec2(m_VisibleSize.width / 2, m_VisibleSize.height / 2));
	m_confirm->runAction(moveConfirm);

	//Debug seed viewer
	/*
	text = "seed: " + seedStr;

	testingText = Label::createWithTTF(text, "fonts/arial.ttf", 30);
	testingText->enableOutline(Color4B::BLACK, 2);
	testingText->setPosition(m_VisibleSize.width / 2, m_VisibleSize.height / 2);
	this->addChild(testingText);

	this->setSeed(seedStr.c_str());*/
}

void MonsterCreate::runCamera()
{
	if (m_confirm != nullptr)
	{
		this->removeChild(m_confirm);
	}

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	LinkJava::JavaEvent();
#endif
}

void MonsterCreate::getData()
{
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	seedStr = LinkJava::GetData();
#endif
}

void MonsterCreate::make()
{
	//dragon, cat, frog, kameleon starters
	int StarterMonsters[TOTAL_INIT_MONSTER_NUM] = {1, 6, 11, 16, 21, 26};
	
	if (m_confirm != nullptr)
	{
		this->removeChild(m_confirm);
	}

    int num = 0;
	int total = TOTAL_INIT_MONSTER_NUM;
	string seed = seedStr;
    int len = MonsterCreate::countBit(seed.c_str());
    int tmSeed;
    
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

    if(atoi(seed.c_str()) != 0)
    {
        srand(atoi(seed.c_str()));
        num = rand() % total;
    }

    else if(seed.find(LineURL) != string::npos)
    {
        const char *s = seed.c_str();
        int i = 0;
        for(int ii = 0; ii < len; ii ++)
        {
            i += s[ii];
        }
        srand(i);
        num = rand() % total;
    }
    
    else
    {
        srand(len);
        tmSeed = rand() % len;
        for(int ii = 0; ii < 3; ii ++)
            tmSeed += rand() % 10;
        srand(tmSeed);
        num = rand() % total;
    }

	if (num < total)
	{
		auto fileU = FileUtils::getInstance();
		auto fileContent = fileU->getStringFromFile("data/animData.xml");
		doc.Parse(fileContent.c_str());
		auto spriteDoc = doc.FirstChildElement();

		string path = spriteDoc->FirstChildElement(MonsterNameData[StarterMonsters[num]].c_str())->FirstChildElement("spriteList")->FirstChildElement("animation")->FirstChildElement("stand")->GetText();

		Sprite *Monster = Sprite::create(path.c_str());
		Monster->setScale(0);
		Monster->setPosition(Vec2(m_VisibleSize.width / 2, m_VisibleSize.height * 2 / 5));
		this->addChild(Monster, imgTag::e_Monster);
		auto action = ScaleTo::create(ActionTime, 1.0f*m_Mag);
		auto fadein = FadeIn::create(ActionTime);
		auto jumpAction = JumpTo::create(ActionTime, Vec2(m_VisibleSize.width / 2, m_VisibleSize.height * 2 / 5), 200 * m_Mag, 1);
		Monster->runAction(action);
		Monster->runAction(fadein);
		Monster->runAction(jumpAction);

		UserDefault::getInstance()->setIntegerForKey(SaveDataKey[(n_DataKeyNum::eMonsterData01) + m_slot].c_str(), StarterMonsters[num]);
		UserDefault::getInstance()->setIntegerForKey(SaveDataKey[(n_DataKeyNum::eMonster1Exp) + m_slot].c_str(), 0);
		UserDefault::getInstance()->setIntegerForKey(SaveDataKey[(n_DataKeyNum::eWinNum01) + m_slot].c_str(), 0);
		UserDefault::getInstance()->setIntegerForKey(SaveDataKey[(n_DataKeyNum::eLossNum01) + m_slot].c_str(), 0);
		UserDefault::getInstance()->setBoolForKey(SaveDataKey[n_DataKeyNum::eKnownData01 + StarterMonsters[num]].c_str(), true);
	}
#else
	auto fileU = FileUtils::getInstance();
	auto fileContent = fileU->getStringFromFile("data/monsterData.xml");
	doc.Parse(fileContent.c_str());
	auto spriteDoc = doc.FirstChildElement();
	int number = atoi(spriteDoc->FirstChildElement("current")->GetText());
	num = StarterMonsters[number];

	fileU = FileUtils::getInstance();
	fileContent = fileU->getStringFromFile("data/animData.xml");
	doc.Parse(fileContent.c_str());
	spriteDoc = doc.FirstChildElement();

	string path = spriteDoc->FirstChildElement(MonsterNameData[num].c_str())->FirstChildElement("spriteList")->FirstChildElement("animation")->FirstChildElement("stand")->GetText();

	Sprite *Monster = Sprite::create(path.c_str());
	Monster->setScale(0);
	Monster->setPosition(Vec2(m_VisibleSize.width / 2, m_VisibleSize.height * 2 / 5));
	this->addChild(Monster, imgTag::e_Monster);
	auto action = ScaleTo::create(ActionTime, 1.0f*m_Mag);
	auto fadein = FadeIn::create(ActionTime);
	auto jumpAction = JumpTo::create(ActionTime, Vec2(m_VisibleSize.width / 2, m_VisibleSize.height * 2 / 5), 200 * m_Mag, 1);
	Monster->runAction(action);
	Monster->runAction(fadein);
	Monster->runAction(jumpAction);

	UserDefault::getInstance()->setIntegerForKey(SaveDataKey[(n_DataKeyNum::eMonsterData01) + m_slot].c_str(), num);
	UserDefault::getInstance()->setIntegerForKey(SaveDataKey[(n_DataKeyNum::eMonster1Exp) + m_slot].c_str(), 0);
	UserDefault::getInstance()->setIntegerForKey(SaveDataKey[(n_DataKeyNum::eWinNum01) + m_slot].c_str(), 0);
	UserDefault::getInstance()->setIntegerForKey(SaveDataKey[(n_DataKeyNum::eLossNum01) + m_slot].c_str(), 0);
	UserDefault::getInstance()->setBoolForKey(SaveDataKey[n_DataKeyNum::eKnownData01 + num].c_str(), true);

	for (int i = 0; i < 31; i++)
	{
		UserDefault::getInstance()->setBoolForKey(SaveDataKey[n_DataKeyNum::eKnownData01 + i].c_str(), true);
	}
#endif

	m_IsMakeEnd = true;

}

void MonsterCreate::sprite()
{
    auto bg = Sprite::create("img/BG/menu.png");
    bg->setScale(m_Mag);
    bg->setPosition(Vec2(m_VisibleSize.width/2, m_VisibleSize.height/2));
    this->addChild(bg, imgTag::e_BG);
    CCLOG("bg\nx:%d y:%d", (int)bg->getPositionX(), (int)bg->getPositionY());
    
    //    m_TapFont = CCSprite::create("Img/tap.png");
    //    m_TapFont->setPosition(ccp(m_VisibleSize.width/2, m_VisibleSize.height/2));
    //    m_TapFont->setScale(m_Mag);
    //    m_TapFont->setOpacity(0);
    //    this->addChild(m_TapFont, n_MC::e_TapFont);
    //    CCActionInterval *fadein = CCFadeIn::create(2.0f);
    //    CCActionInterval *fadeout = CCFadeOut::create(1.0f);
    //    CCSpawn *spawn = CCSpawn::create(fadein, fadeout);
    //    CCRepeatForever *repeatForever = CCRepeatForever::create(spawn);
    //    m_TapFont->runAction(repeatForever);
}

bool MonsterCreate::onTouchBegan(Touch* pTouch, Event* pEvent)
{
    return true;
}

void MonsterCreate::onTouchEnded(Touch* pTouch, Event* pEvent)
{
    
    if(m_IsMakeEnd == true)
    {
        Scene *next = MenuScene::createScene();
        Scene *pScene = CCTransitionCrossFade::create(1.0f, next);
        Director::getInstance()->replaceScene(pScene);
    }
    else
    {
        CCUserDefault::getInstance()->setBoolForKey("IsSeedGet", false);
        m_IsMakeEnd = true;
        m_IsActiv = true;
        //m_TapFont->setVisible(false);
        this->make();
    }
}

void MonsterCreate::setSeed(const char* seedData)
{
    int len = 0;
    len = countBit(seedData);
	int tmSeed = 0;
    srand(len);
    for(int ii = 0; ii < 3; ii ++)
        tmSeed += rand() % 10;
    srand(tmSeed);
    int seed = 0;
    seed = rand() % 3 + 1;
    CCUserDefault::getInstance()->setIntegerForKey("Seed", seed);
    CCUserDefault::getInstance()->setBoolForKey("IsSeedGet", true);
    CCUserDefault::getInstance()->flush();
}

int MonsterCreate::countBit(const char* data)
{
    string st = data;
    
    return st.length();
}

void setMonsterLog(){
    auto log = UserDefault::getInstance();
//    log->setStringForKey("monsterLog", <#const std::string &value#>)
}
