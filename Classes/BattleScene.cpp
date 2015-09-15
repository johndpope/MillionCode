#include "BattleScene.h"
#include "ResultScene.h"
#include "AudioControl.h"

using namespace cocos2d;
using namespace std;

enum SpriteTags
{
    ReturnBtn,
};

BattleScene::BattleScene()
{
	m_pickingPhase = new Picking(this);
}

BattleScene::~BattleScene()
{
	delete m_pickingPhase;
	m_pickingPhase = 0;
}

Scene* BattleScene::createScene() {
    auto scene = Scene::create();
    auto layer = BattleScene::create();
    scene->addChild(layer);
    return scene;
}

bool BattleScene::init() {
    if ( !Layer::init() ) { return false; }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    m_Mag = Generic::getScreenMagnification(visibleSize);

    displayAnimBG();
	runBattle();

	this->scheduleUpdate();
    
    return true;
}

void BattleScene::runBattle()
{
	UserDefault* def = UserDefault::getInstance();
	m_pickingPhase->renderPicking(def->getIntegerForKey("Battle"));
}

void BattleScene::update(float dt)
{
	m_pickingPhase->update(dt);

	for (int i = 0; i < 0; i++)
	{
		cardData[i] = m_pickingPhase->getCardData(i);
	}
}

void BattleScene::displayAnimBG()
{
	Sprite* sprite = Sprite::create("img/BG/BattleBG/battleBG.jpg");
	sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	sprite->setScale(m_Mag*1.2);
	this->addChild(sprite);
	/*
    CCLOG("anim");
	Sprite* sprite = Sprite::create("img/BG/BattleBG/bg00001.jpg");
	Animation* anim = Animation::create();

	anim->addSpriteFrameWithFileName("img/BG/BattleBG/bg00002.jpg");
	anim->addSpriteFrameWithFileName("img/BG/BattleBG/bg00003.jpg");
	anim->addSpriteFrameWithFileName("img/BG/BattleBG/bg00004.jpg");
	anim->addSpriteFrameWithFileName("img/BG/BattleBG/bg00005.jpg");
	anim->addSpriteFrameWithFileName("img/BG/BattleBG/bg00006.jpg");
	anim->addSpriteFrameWithFileName("img/BG/BattleBG/bg00007.jpg");
	anim->addSpriteFrameWithFileName("img/BG/BattleBG/bg00008.jpg");
	anim->addSpriteFrameWithFileName("img/BG/BattleBG/bg00009.jpg");
	anim->addSpriteFrameWithFileName("img/BG/BattleBG/bg00010.jpg");
	anim->addSpriteFrameWithFileName("img/BG/BattleBG/bg00011.jpg");
	anim->addSpriteFrameWithFileName("img/BG/BattleBG/bg00012.jpg");
	anim->addSpriteFrameWithFileName("img/BG/BattleBG/bg00013.jpg");
	anim->addSpriteFrameWithFileName("img/BG/BattleBG/bg00014.jpg");
	anim->addSpriteFrameWithFileName("img/BG/BattleBG/bg00015.jpg");
	anim->addSpriteFrameWithFileName("img/BG/BattleBG/bg00016.jpg");
	anim->addSpriteFrameWithFileName("img/BG/BattleBG/bg00017.jpg");
	anim->addSpriteFrameWithFileName("img/BG/BattleBG/bg00018.jpg");
	anim->addSpriteFrameWithFileName("img/BG/BattleBG/bg00019.jpg");
	anim->addSpriteFrameWithFileName("img/BG/BattleBG/bg00020.jpg");
	anim->addSpriteFrameWithFileName("img/BG/BattleBG/bg00021.jpg");
	anim->addSpriteFrameWithFileName("img/BG/BattleBG/bg00022.jpg");
	anim->addSpriteFrameWithFileName("img/BG/BattleBG/bg00023.jpg");
	anim->addSpriteFrameWithFileName("img/BG/BattleBG/bg00024.jpg");
	anim->addSpriteFrameWithFileName("img/BG/BattleBG/bg00025.jpg");
	anim->addSpriteFrameWithFileName("img/BG/BattleBG/bg00026.jpg");
	anim->addSpriteFrameWithFileName("img/BG/BattleBG/bg00027.jpg");
	anim->addSpriteFrameWithFileName("img/BG/BattleBG/bg00028.jpg");
	anim->addSpriteFrameWithFileName("img/BG/BattleBG/bg00029.jpg");
	anim->addSpriteFrameWithFileName("img/BG/BattleBG/bg00030.jpg");
	anim->addSpriteFrameWithFileName("img/BG/BattleBG/bg00031.jpg");
	anim->addSpriteFrameWithFileName("img/BG/BattleBG/bg00032.jpg");
	anim->addSpriteFrameWithFileName("img/BG/BattleBG/bg00033.jpg");
	anim->addSpriteFrameWithFileName("img/BG/BattleBG/bg00034.jpg");
	anim->addSpriteFrameWithFileName("img/BG/BattleBG/bg00035.jpg");

	anim->setLoops(-1);
	anim->setDelayPerUnit(0.1f);
	//sprite->setColor(Color3B(100,100,100));
	sprite->runAction(Animate::create(anim));
	sprite->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    sprite->setScale(m_Mag*0.8);
    
	this->addChild(sprite);
	*/

	auto particles = ParticleSystemQuad::create("img/BG/BattleBG/battleBG.plist");
	particles->setPosition(visibleSize.width / 2, visibleSize.height / 2);

	this->addChild(particles);
}

void BattleScene::backBtn()
{
	string btn = "img/UI/menu/UI_M_009.png";
	string pushBtn = "img/UI/menu/UI_M_010.png";

	auto callBackItem = [](Ref *obj){
		auto nextScene = ResultScene::createScene();
		auto pScene = TransitionFade::create(0.5f, nextScene);
		Director::getInstance()->replaceScene(pScene);
	};

	auto btnItem = MenuItemImage::create(btn.c_str(),
		pushBtn.c_str(),
		callBackItem);
	btnItem->setScale(m_Mag);
	btnItem->setTag(SpriteTags::ReturnBtn);
	Menu* rtnBtn = Menu::create(btnItem, NULL);
	rtnBtn->setPosition(Vec2(origin.x + visibleSize.width - btnItem->getContentSize().width / 2,
		origin.y + btnItem->getContentSize().height / 2));

	this->addChild(rtnBtn);
}
