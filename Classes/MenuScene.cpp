#include "MenuScene.h"
#include "TitleScene.h"
#include "BattleScene.h"
#include "CheckScene.h"
#include "MonsterCreate.h"
#include "FoodCreate.h"
#include "MonsterEqData.h"
#include "DataKey.h"
#include "VersusScene.h"
#include "Bestiary.h"
#include "AudioControl.h"

using namespace cocos2d;
using namespace std;

bool MenuScene::m_monsterMenuEnable = false;

enum SpriteTag {
    e_BattleBtn,
	e_MonsterBtn,
	e_CreateBtn,
	e_StatusBtn,
	e_BestiaryBtn,
	e_Total
};

Scene* MenuScene::createScene() {
    auto scene = Scene::create();
    auto layer = MenuScene::create();
    scene->addChild(layer);
    return scene;
}

bool MenuScene::init() {
    if ( !Layer::init() ){ return false; }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    m_Mag = Generic::getScreenMagnification(visibleSize);

	for (int i = 0; i < 5; i++)
		buttonPressed[i] = false;

	readyToBack = false;

	displayBackground();
    setUserInterface();
	animateButtons();
	eventHandler();
    backBtn();

    return true;
}

void MenuScene::eventHandler()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MenuScene::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(MenuScene::onTouchEnded, this);
	listener->onTouchCancelled = CC_CALLBACK_2(MenuScene::onTouchCancelled, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

bool MenuScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* eventt)
{
	Rect touchPoint = Rect(touch->getLocation().x, touch->getLocation().y, 2, 2);

	Sprite* buttonArray[5] = { m_battleBtn, m_monsterBtn, m_createBtn, m_statusBtn, m_bestiaryBtn };

	for (int i = 0; i < SpriteTag::e_Total; i++)
	{
		auto Button = buttonArray[i];
		if (readyToBack)
		{
			if (touchPoint.intersectsRect(Button->getBoundingBox()))
			{
				buttonPressed[i] = true;
				Button->setColor(Color3B(100, 100, 100));
			}
		}
	}

	return true;
}

void MenuScene::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* eventt)
{
	
}

void MenuScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* eventt)
{
	Rect touchPoint = Rect(touch->getLocation().x, touch->getLocation().y, 2, 2);

	Sprite* buttonArray[5] = { m_battleBtn, m_monsterBtn, m_createBtn, m_statusBtn, m_bestiaryBtn };
	for (int i = 0; i < SpriteTag::e_Total; i++)
	{
		buttonArray[i]->setColor(Color3B(255, 255, 255));
	}

	for (int i = 0; i < SpriteTag::e_Total; i++)
	{
		auto Button = buttonArray[i];
		if (buttonPressed[i] == true)
		{
			if (touchPoint.intersectsRect(Button->getBoundingBox()))
			{
				sceneTransition(i);
			}
		}
	}

	for (int i = 0; i < 5; i++)
	{
		buttonPressed[i] = false;
	}
}

void MenuScene::update(float dt)
{
	
}

void MenuScene::animateButtons()
{
	

	//Main menu group
	auto battleMove = MoveTo::create(0.5f, Vec2(visibleSize.width / 1.4f, visibleSize.height / 1.4f));
	auto monsterMove = MoveTo::create(0.5f, Vec2(visibleSize.width / 1.4f, visibleSize.height/4));
	auto battleAway = MoveTo::create(0.5f, Vec2(visibleSize.width + 300, visibleSize.height / 1.4f));
	auto monsterAway = MoveTo::create(0.5f, Vec2(visibleSize.width + 300, visibleSize.height / 4));

	//Monster Menu group
	auto createMove = MoveTo::create(0.5f, Vec2(visibleSize.width / 1.4f, (visibleSize.height / 2) + ((visibleSize.height/2)/2)));
	auto createAway = MoveTo::create(0.5f, Vec2(visibleSize.width + 300, (visibleSize.height / 2) + ((visibleSize.height / 2) / 2)));
	auto statusMove = MoveTo::create(0.5f, Vec2(visibleSize.width / 1.4f, visibleSize.height / 2));
	auto statusAway = MoveTo::create(0.5f, Vec2(visibleSize.width + 300, visibleSize.height / 2));
	auto bestiaryMove = MoveTo::create(0.5f, Vec2(visibleSize.width / 1.4f, (visibleSize.height - visibleSize.height / 2) /2));
	auto bestiaryAway = MoveTo::create(0.5f, Vec2(visibleSize.width + 300, (visibleSize.height - visibleSize.height / 2) / 2));

	if (m_monsterMenuEnable == false)
	{
		readyToBack = false;
		m_monsterBtn->runAction(monsterMove);

		m_createBtn->runAction(createAway);
		m_statusBtn->runAction(statusAway);
		m_bestiaryBtn->runAction(bestiaryAway);

		auto enableBack = CallFunc::create([this](){this->enableBackButton(); });
		m_battleBtn->runAction(Sequence::create(battleMove, enableBack, NULL));
	}
	else
	{
		readyToBack = false;
		m_createBtn->runAction(createMove);
		m_statusBtn->runAction(statusMove);
		m_bestiaryBtn->runAction(bestiaryMove);

		m_monsterBtn->runAction(monsterAway);

		auto enableBack = CallFunc::create([this](){this->enableBackButton(); });
		m_battleBtn->runAction(Sequence::create(battleAway, enableBack, NULL));
	}
}

void MenuScene::resetButtons()
{
	if (m_monsterMenuEnable == false)
	{
		m_battleBtn->setPosition(Vec2(visibleSize.width / 1.4, visibleSize.height + 100));
		m_monsterBtn->setPosition(Vec2(visibleSize.width / 1.4, -100));
	}
	else
	{
		m_createBtn->setPosition(Vec2(visibleSize.width / 1.4, visibleSize.height + 200));
		m_statusBtn->setPosition(Vec2(visibleSize.width / 1.4, visibleSize.height + 100));
		m_bestiaryBtn->setPosition(Vec2(visibleSize.width / 1.4, -100));
	}
}

void MenuScene::enableBackButton()
{
	readyToBack = true;
}

void MenuScene::setUserInterface() 
{
	//initialize buttons in non-visible place
	auto rect = Rect(10, 65, 390, 165);

	//Battle Button
	m_battleBtn = Sprite::create("img/UI/menu/UI_Home_001.png");
	m_battleBtn->setTag(SpriteTag::e_BattleBtn);
	m_battleBtn->setPosition(Vec2(visibleSize.width / 1.4, visibleSize.height + m_battleBtn->getBoundingBox().getMaxY()));
	m_battleBtn->setTextureRect(rect);
	this->addChild(m_battleBtn);
	//Monster Button
	m_monsterBtn = Sprite::create("img/UI/menu/UI_Home_007.png");
	m_monsterBtn->setTag(SpriteTag::e_MonsterBtn);
	m_monsterBtn->setPosition(Vec2(visibleSize.width / 1.4, -m_monsterBtn->getBoundingBox().getMaxY()));
	m_monsterBtn->setTextureRect(rect);
	this->addChild(m_monsterBtn);
	//Create Button
	m_createBtn = Sprite::create("img/UI/menu/UI_Home_011.png");
	m_createBtn->setTag(SpriteTag::e_CreateBtn);
	m_createBtn->setPosition(Vec2(visibleSize.width + 300, visibleSize.height + (m_createBtn->getBoundingBox().getMaxY() * 2)));
	m_createBtn->setTextureRect(rect);
	this->addChild(m_createBtn);
	//Status Button
	m_statusBtn = Sprite::create("img/UI/menu/UI_Home_009.png");
	m_statusBtn->setTag(SpriteTag::e_StatusBtn);
	m_statusBtn->setPosition(Vec2(visibleSize.width + 300, visibleSize.height + m_statusBtn->getBoundingBox().getMaxY()));
	m_statusBtn->setTextureRect(rect);
	this->addChild(m_statusBtn);
	//Bestiary Button
	m_bestiaryBtn = Sprite::create("img/UI/menu/UI_Home_005.png");
	m_bestiaryBtn->setTag(SpriteTag::e_BestiaryBtn);
	m_bestiaryBtn->setPosition(Vec2(visibleSize.width + 300, -m_bestiaryBtn->getBoundingBox().getMaxY()));
	m_bestiaryBtn->setTextureRect(rect);
	this->addChild(m_bestiaryBtn);
}

void MenuScene::displayBackground()
{

	
	
	//Moving BG
	Sprite* bg = Sprite::create("img/BG/MenuBG/main_00000.png");
	//bg->setColor(Color3B(100, 100, 100));
	Animation* anim = Animation::create();

	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00001.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00002.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00003.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00004.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00005.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00006.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00007.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00008.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00009.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00010.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00011.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00012.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00013.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00014.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00015.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00016.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00017.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00018.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00019.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00020.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00021.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00022.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00023.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00024.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00025.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00026.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00027.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00028.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00029.png");

	anim->setLoops(-1);
	anim->setDelayPerUnit(0.1f);
	//sprite->setColor(Color3B(100,100,100));
	bg->runAction(Animate::create(anim));
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	bg->setScale(m_Mag * 1.4);
	//bg->setOpacity(80);
	this->addChild(bg);

	auto blendingBG = Sprite::create("img/BG/menu.png");
	blendingBG->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	blendingBG->setScale(m_Mag);
	blendingBG->setOpacity(150);
	this->addChild(blendingBG);

	//-----------------------Load Live2D animated Sprite-------------------------------------------------------------------------------
	UserDefault* def = UserDefault::getInstance();
	int key = def->getIntegerForKey(SaveDataKey[n_DataKeyNum::eMonsterData01].c_str());

	float scale;
	float posX;
	float posY;

	switch (key)
	{
	case 4:
		scale = 1.9f;
		posX = 1.4f;
		posY = 1.75f;
		break;
	case 14:
		scale = 1.0f;
		posX = 0.95f;
		posY = 0.9f;
		break;
	case 16:
		scale = 1.3f;
		posX = 1.1f;
		posY = 1.2f;
		break;
	case 18:
		scale = 0.5f;
		posX = 0.5f;
		posY = 1.2f;
		break;
	default:
		scale = 1.2f;
		posX = 1.0f;
		posY = 1.1f;
		break;
	}

	pixie = Live2DSprite::createDrawNode(MonsterNameData[key], scale, scale, posX, posY); //Flag Monster Here <<-------------------------------------------------------
    this->addChild(pixie);
}

void MenuScene::sceneTransition(int btnTag) 
{
    Scene* nextScene = nullptr;

    switch (btnTag) 
	{
        case SpriteTag::e_BattleBtn:
            MenuScene::m_monsterMenuEnable = false;
            nextScene = VersusScene::createScene();
            break;
        case SpriteTag::e_StatusBtn:
			MenuScene::m_monsterMenuEnable = true;
            nextScene = CheckScene::createScene();
			break;
		case SpriteTag::e_MonsterBtn:
			MenuScene::m_monsterMenuEnable = true;
			resetButtons();
			animateButtons();
			break;
		case SpriteTag::e_CreateBtn:
			MenuScene::m_monsterMenuEnable = true;
			nextScene = MonsterCreate::createScene();
			break;
		case SpriteTag::e_BestiaryBtn:
			MenuScene::m_monsterMenuEnable = true;
			nextScene = Bestiary::createScene();
        default:
            break;
    }
    
    if(nextScene != nullptr) 
	{
        auto pScene = TransitionFade::create(0.5f, nextScene);
        Director::getInstance()->replaceScene(pScene);
    }
}

void MenuScene::showEqMenu(cocos2d::Ref *pSender)
{
	MenuScene::m_monsterMenuEnable = true;
}

void MenuScene::backBtn() 
{
    string btn     = "img/UI/menu/UI_B_005.png";
    string pushBtn = "img/UI/menu/UI_B_005.png";
    auto titleBtnItem = MenuItemImage::create(btn.c_str(),
                                          pushBtn.c_str(),
                                          CC_CALLBACK_1(MenuScene::rtnTitleScene, this));
    titleBtnItem->setScale(m_Mag * 1.5);
    titleBtnItem->setPosition(Vec2(origin.x + visibleSize.width - titleBtnItem->getBoundingBox().getMaxX(),
		origin.y + titleBtnItem->getBoundingBox().getMaxY()));
    auto pMenu = Menu::create(titleBtnItem, NULL);
    pMenu->setPosition(Point::ZERO);
    this->addChild(pMenu);

	
}

void MenuScene::rtnTitleScene(cocos2d::Ref *pSender)
{
	if (m_monsterMenuEnable)
	{
		if (readyToBack)
		{
			m_monsterMenuEnable = false;
			resetButtons();
			animateButtons();
		}
	}
	else
	{
		auto pScene = TransitionFade::create(0.5f, TitleScene::createScene());
		Director::getInstance()->replaceScene(pScene);
	}
}