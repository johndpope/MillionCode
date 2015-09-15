#include "TitleScene.h"
#include "MenuScene.h"
#include "DataKey.h"
#include "MonsterEqData.h"
#include "TutorialScene.h"

using namespace cocos2d;
using namespace std;

enum SpriteTag
{
    e_BackGround,
    e_StartButton
};

Scene* TitleScene::createScene() {
    auto scene = Scene::create();
    auto layer = TitleScene::create();
    scene->addChild(layer);
    return scene;
}

bool TitleScene::init() 
{
    if ( !Layer::init() ) 
	{
		return false; 
	}

	//glClearColor(255, 255, 255, 255);
    
    visibleSize = Director::getInstance()->getVisibleSize();
    m_Mag = Generic::getScreenMagnification(visibleSize);

	UserDefault* def = UserDefault::getInstance();
	def->setIntegerForKey("Battle", 0);

	displayBG();
	setSound();
    displayMenu(Generic::checkSaveData());

	this->scheduleUpdate();
    
    return true;
}

void TitleScene::setSound()
{
    AudioControl::createBgm("sound/bgm/BGM.mp3", 1.0f);
    AudioControl::playBgm(true);
}

void TitleScene::displayMenu(bool loadContent)
{
	MenuItemFont::setFontSize(60);
	MenuItemFont* newGameItem = MenuItemFont::create("NEW GAME", CC_CALLBACK_1(TitleScene::menuSceneTransition, this, true));
	MenuItemFont* continueItem = MenuItemFont::create("CONTINUE", CC_CALLBACK_1(TitleScene::menuSceneTransition, this, false));

	auto label1 = Label::createWithTTF("NEW GAME", "fonts/arial.ttf", 45);
	auto label2 = Label::createWithTTF("CONTINUE", "fonts/arial.ttf", 45);
	label1->enableOutline(Color4B::WHITE, 2);
	label2->enableOutline(Color4B::WHITE, 2);
	newGameItem->setLabel(label1);
	continueItem->setLabel(label2);
	if (!loadContent)
	{
		continueItem->setEnabled(false);
	}
	loadMenu = Menu::create(newGameItem, continueItem, NULL);
	loadMenu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 3));
	loadMenu->alignItemsVerticallyWithPadding(30);
	loadMenu->setVisible(false);
	this->addChild(loadMenu);

    string btn     = "img/UI/home/UI_T_002.png";
    string pushBtn = "img/UI/home/UI_T_003.png";
    
    auto startBtn = MenuItemImage::create(btn.c_str(),
                                          pushBtn.c_str(),
                                          CC_CALLBACK_1(TitleScene::showLoadMenu, this, loadMenu));
    startBtn->setScale(m_Mag);
    
    startMenu = Menu::create(startBtn, NULL);
    startMenu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 3));
    this->addChild(startMenu);

	//Fade in - Fade out animation
	cocos2d::Vector<cocos2d::FiniteTimeAction*> fadeAnimation;
	fadeAnimation.pushBack(FadeOut::create(3));
	fadeAnimation.pushBack(FadeIn::create(3));

	auto sequence = Sequence::create(fadeAnimation);

	auto repetition = RepeatForever::create(sequence);

	startMenu->runAction(repetition);
}

void TitleScene::displayBG()
{
	auto particles = ParticleSystemQuad::create("img/BG/particle_texture1.plist");
	particles->setPosition(visibleSize.width / 2, visibleSize.height / 2);

	this->addChild(particles);

	bg = Sprite::create("img/BG/alt_title(caps).png");

	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	bg->setScale(m_Mag);
	bg->setTag(SpriteTag::e_BackGround);
	bg->setOpacity(200);
	this->addChild(bg);

	bg2 = Sprite::create("img/BG/alt_title2(caps).png");
	bg2->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	bg2->setScale(m_Mag);
	bg2->setTag(SpriteTag::e_BackGround);
	bg2->setVisible(false);
	this->addChild(bg2);


	auto fileU = FileUtils::getInstance();
	auto fileContent = fileU->getStringFromFile("data/animData.xml");
	doc.Parse(fileContent.c_str());

	srand(time(NULL));
	auto monster1 = rand() % 17;
	auto monster2 = rand() % 17;
	auto monster3 = rand() % 17;

	auto mSpritePath = doc.FirstChildElement()->FirstChildElement(MonsterNameData[monster1].c_str())->FirstChildElement("spriteList")->FirstChildElement("animation")->FirstChildElement("stand")->GetText();
	auto monsterSprite1 = Sprite::create(mSpritePath);
	monsterSprite1->setPosition(Vec2(rand() % (int)visibleSize.width, rand() % (int)visibleSize.height));
	monsterSprite1->setOpacity(100);
	monsterSprite1->setScale(m_Mag *0.8);
	monsterSprite1->setVisible(false);
	this->addChild(monsterSprite1);

	mSpritePath = doc.FirstChildElement()->FirstChildElement(MonsterNameData[monster2].c_str())->FirstChildElement("spriteList")->FirstChildElement("animation")->FirstChildElement("stand")->GetText();
	auto monsterSprite2 = Sprite::create(mSpritePath);
	monsterSprite2->setPosition(Vec2(rand() % (int)visibleSize.width, rand() % (int)visibleSize.height));
	monsterSprite2->setOpacity(100);
	monsterSprite2->setScale(m_Mag *0.8);
	monsterSprite2->setVisible(false);
	this->addChild(monsterSprite2);

	mSpritePath = doc.FirstChildElement()->FirstChildElement(MonsterNameData[monster3].c_str())->FirstChildElement("spriteList")->FirstChildElement("animation")->FirstChildElement("stand")->GetText();
	auto monsterSprite3 = Sprite::create(mSpritePath);
	monsterSprite3->setPosition(Vec2(rand() % (int)visibleSize.width, rand() % (int)visibleSize.height));
	monsterSprite3->setOpacity(100);
	monsterSprite3->setScale(m_Mag *0.8);
	monsterSprite3->setVisible(false);
	this->addChild(monsterSprite3);

	auto showM = Show::create();
	auto fadeInM1 = FadeTo::create(2.0f, 100);
	auto fadeOutM1 = FadeOut::create(2.0f);
	auto fadeInM2 = FadeTo::create(2.0f, 100);
	auto fadeOutM2 = FadeOut::create(2.0f);
	auto fadeInM3 = FadeTo::create(2.0f, 100);
	auto fadeOutM3 = FadeOut::create(2.0f);
	

	monsterSprite1->runAction(RepeatForever::create(Sequence::create(DelayTime::create(3.0f), showM, fadeInM1, fadeOutM1, DelayTime::create(5.0f), NULL)));
	monsterSprite2->runAction(RepeatForever::create(Sequence::create(DelayTime::create(6.0f), showM, fadeInM2, fadeOutM2, DelayTime::create(5.0f), NULL)));
	monsterSprite3->runAction(RepeatForever::create(Sequence::create(DelayTime::create(9.0f), showM, fadeInM3, fadeOutM3, DelayTime::create(5.0f), NULL)));
}

void TitleScene::menuSceneTransition(cocos2d::Ref *pSender, bool newGame)
{
	const int maxNumMonsters = 3;
	const int maxNumEquip = 10;

	if (newGame)
	{
		if (Generic::checkSaveData())
		{
			auto nextScene = TutorialScene::createScene();
			auto pScene = TransitionFade::create(1.0f, nextScene);
			Director::getInstance()->replaceScene(pScene);
		}
		else
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

			auto nextScene = MenuScene::createScene();
			auto pScene = TransitionFade::create(1.0f, nextScene);
			Director::getInstance()->replaceScene(pScene);
		}
		return;
	}
    
    auto nextScene = MenuScene::createScene();
    auto pScene = TransitionFade::create(0.5f, nextScene);
    Director::getInstance()->replaceScene(pScene);
}

void TitleScene::showLoadMenu(cocos2d::Ref* pSender, cocos2d::Menu* menu)
{
	menu->setVisible(true);
}

void TitleScene::update(float dt)
{
	if (loadMenu->isVisible() == true)
	{
		startMenu->setVisible(false);
		bg->setVisible(false);
		bg2->setVisible(true);
	}
}
