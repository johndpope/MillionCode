#include "TutorialScene.h"
#include "Generic.h"
#include "TitleScene.h"
#include "MonsterEqData.h"
#include "DataKey.h"
#include "MenuScene.h"
#include "LinkJava.h"

using namespace cocos2d;
using namespace std;

Scene* TutorialScene::createScene()
{
	Scene *scene = Scene::create();
	auto layer = TutorialScene::create();
	scene->addChild(layer);
	return scene;
}

// on "init" you need to initialize your instance
bool TutorialScene::init()
{
	if (!CCLayer::init()) { return false; }

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//LinkJava::JavaEvent();
#endif

	visibleSize = Director::getInstance()->getVisibleSize();
	m_Mag = Generic::getScreenMagnification(visibleSize);
	origin = Director::getInstance()->getVisibleOrigin();

	
	//setBackBtn();
	setConfirm();


	return true;
}

void TutorialScene::setBackBtn()
{
	/*
	string btn = "img/UI/menu/UI_M_009.png";
	string pushBtn = "img/UI/menu/UI_M_010.png";
	auto titleBtnItem = MenuItemImage::create(btn.c_str(),
		pushBtn.c_str(),
		CC_CALLBACK_1(TutorialScene::rtrnTitleScene, this));
	titleBtnItem->setScale(m_Mag);
	titleBtnItem->setPosition(Vec2(origin.x + visibleSize.width - titleBtnItem->getContentSize().width / 2,
		origin.y + titleBtnItem->getContentSize().height / 2));
	auto pMenu = Menu::create(titleBtnItem, NULL);
	pMenu->setPosition(Point::ZERO);
	this->addChild(pMenu);
	*/
}

void TutorialScene::rtrnTitleScene(cocos2d::Ref *pSender)
{
	auto nextScene = TitleScene::createScene();
	auto pScene = TransitionFade::create(0.5f, nextScene);
	Director::getInstance()->replaceScene(pScene);
}

void TutorialScene::setConfirm()
{
	const int maxNumMonsters = 3;
	const int maxNumEquip = 10;

	if (Generic::checkSaveData())//If there is data - Display confirmation menu to reset it
	{
		
		auto confirmText = Label::createWithTTF("データを消してもよろしいですか", "fonts/ant-maru.ttf", 45);
		confirmText->enableOutline(Color4B::WHITE, 2);
		confirmText->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 1.5));
		this->addChild(confirmText);
		
		MenuItemFont::setFontSize(60);
		MenuItemFont* yesItem = MenuItemFont::create("YES", CC_CALLBACK_1(TutorialScene::menuSceneTransition, this));
		MenuItemFont* noItem = MenuItemFont::create("NO", CC_CALLBACK_1(TutorialScene::rtrnTitleScene, this));
		auto label1 = Label::createWithTTF("はい", "fonts/ant-maru.ttf", 45);
		auto label2 = Label::createWithTTF("いいえ", "fonts/ant-maru.ttf", 45);
		label1->enableOutline(Color4B::WHITE, 2);
		label2->enableOutline(Color4B::WHITE, 2);
		yesItem->setLabel(label1);
		noItem->setLabel(label2);

		confirmMenu = Menu::create(yesItem, noItem, NULL);
		confirmMenu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 3));
		confirmMenu->alignItemsVerticallyWithPadding(30);
		this->addChild(confirmMenu);
	}
	else
	{
        
		/*
		resetSaveData();
        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        
        listener->onTouchBegan = [](Touch* touch, Event* event)
        {
            return true;
        };
        
        listener->onTouchEnded = [](Touch* touch, Event* event)
        {
            auto nextScene = MenuScene::createScene();
            auto pScene = TransitionFade::create(1.0f, nextScene);
            Director::getInstance()->replaceScene(MenuScene::createScene());
            CCLOG("Test");
        };
        
        
        this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
		*/
		auto tmpNode = Node::create();
		auto transition = CallFunc::create([this](){this->continueToMenu(); });
		tmpNode->runAction(transition);
	}
}

void TutorialScene::resetSaveData()
{
	const int maxNumMonsters = 3;
	const int maxNumKnown = 31;

	//データをリセット
	//Set every SaveDataKey for Monsters and Equipment to 0 (eEmpty)
	UserDefault* def = UserDefault::getInstance();

	for (int i = 0; i < maxNumMonsters; i++)
	{
		def->setIntegerForKey(SaveDataKey[n_DataKeyNum::eMonsterData01 + i].c_str(), n_MonsterData::eEmpty);

	}
	for (int i = 0; i < maxNumKnown; i++)
	{
		def->setBoolForKey(SaveDataKey[n_DataKeyNum::eKnownData01 + i].c_str(), false);
	}
	def->setBoolForKey(SaveDataKey[n_DataKeyNum::eKnownData01].c_str(), true);

	def->setIntegerForKey(SaveDataKey[n_DataKeyNum::eMonster1Exp].c_str(), 0);
	def->setIntegerForKey(SaveDataKey[n_DataKeyNum::eMonster2Exp].c_str(), 0);
	def->setIntegerForKey(SaveDataKey[n_DataKeyNum::eMonster3Exp].c_str(), 0);

	def->setIntegerForKey(SaveDataKey[n_DataKeyNum::eWinNum01].c_str(), 0);
	def->setIntegerForKey(SaveDataKey[n_DataKeyNum::eWinNum02].c_str(), 0);
	def->setIntegerForKey(SaveDataKey[n_DataKeyNum::eWinNum03].c_str(), 0);

	def->setIntegerForKey(SaveDataKey[n_DataKeyNum::eLossNum01].c_str(), 0);
	def->setIntegerForKey(SaveDataKey[n_DataKeyNum::eLossNum02].c_str(), 0);
	def->setIntegerForKey(SaveDataKey[n_DataKeyNum::eLossNum03].c_str(), 0);


	def->flush();
}

void TutorialScene::menuSceneTransition(cocos2d::Ref* pSender)
{
	resetSaveData();
	auto nextScene = MenuScene::createScene();
	auto pScene = TransitionFade::create(0.5f, nextScene);
	Director::getInstance()->replaceScene(pScene);
}

void TutorialScene::continueToMenu()
{
	resetSaveData();
	auto nextScene = MenuScene::createScene();
	auto pScene = TransitionFade::create(0.5f, nextScene);
	Director::getInstance()->replaceScene(pScene);
}