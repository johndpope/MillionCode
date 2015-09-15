#include "ResultScene.h"
#include "MenuScene.h"
#include "DataKey.h"
#include "MonsterEqData.h"

using namespace cocos2d;
using namespace std;

//-------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------//
//                                                                                                 //
//                                 MillionCode XP Formula                                          //
//                                                                                                 //
// TotalXP = BASEXP + ((Enemy Lv. - Player Lv.) * 100) + ((EnemyRarity*20) - (PlayerRarity*10))    //
//                                                                                                 //
//-------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------//

enum SpriteTags
{
    ReturnBtn,
};

Scene* ResultScene::createScene() {
    auto scene = Scene::create();
    auto layer = ResultScene::create();
    scene->addChild(layer);
    return scene;
}

bool ResultScene::init() {
    if ( !Layer::init() ) { return false; }
    
	m_overviewMode = true;
	m_evolvingMode = false;
	m_standBy = false;
	for (int i = 0; i < 3; i++)
		m_evolveState[i] = false;
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    m_Mag = Generic::getScreenMagnification(visibleSize);

	UserDefault* def = UserDefault::getInstance();
	def->setIntegerForKey("Battle", 0);

	displayBG();
	eventHandler();

	displayResult();
    
    return true;
}

void ResultScene::displayResult()
{
	m_marks = Node::create();

	auto fileU = FileUtils::getInstance();
	auto fileContent = fileU->getStringFromFile("data/animData.xml");

	doc.Parse(fileContent.c_str());

	UserDefault* def = UserDefault::getInstance();
	int difficulty;

	difficulty = def->getIntegerForKey(SaveDataKey[n_DataKeyNum::eDiffLevel].c_str());
	winRes[0] = def->getIntegerForKey(SaveDataKey[n_DataKeyNum::eWinResult01].c_str());
	winRes[1] = def->getIntegerForKey(SaveDataKey[n_DataKeyNum::eWinResult02].c_str());
	winRes[2] = def->getIntegerForKey(SaveDataKey[n_DataKeyNum::eWinResult03].c_str());

	//Win = 0, Draw = 1, Lose = 2. ---------  Example: Win + Draw + Lose = 0 + 1 + 2 = 3 = DRAW totalResult.
	int totalResult = winRes[0] + winRes[1] + winRes[2];
	if (totalResult == 3)
	{
		totalResult = DRAW;
	}
	else if (totalResult < 3)
	{
		totalResult = WIN;
	}
	else
	{
		totalResult = LOSE;
	}

	int key;

	for (int i = 0; i < 3; i++)
	{
		key = def->getIntegerForKey(SaveDataKey[n_DataKeyNum::eMonsterData01 + i].c_str());
		auto spritePath = doc.FirstChildElement()->FirstChildElement(MonsterNameData[key].c_str())->FirstChildElement("spriteList")->FirstChildElement("animation")->FirstChildElement("stand")->GetText();
		m_playerMonsters[i] = Sprite::create(spritePath);

		m_playerMonsters[i]->setScale(0.4);
		m_playerMonsters[i]->setPosition(visibleSize.width / 4.5, (visibleSize.height / 8) * (6 - (i * 2)));
		this->addChild(m_playerMonsters[i]);

		key = def->getIntegerForKey(SaveDataKey[n_DataKeyNum::eEnemyMonster01 + i].c_str());
		spritePath = doc.FirstChildElement()->FirstChildElement(MonsterNameData[key].c_str())->FirstChildElement("spriteList")->FirstChildElement("animation")->FirstChildElement("stand")->GetText();
		m_enemyMonsters[i] = Sprite::create(spritePath);

		m_enemyMonsters[i]->setScale(0.4);
		m_enemyMonsters[i]->setPosition(visibleSize.width / 1.25, (visibleSize.height / 8) * (6 - (i * 2)));
		this->addChild(m_enemyMonsters[i]);

		if (winRes[i] == LOSE)
		{
			int lossNum = def->getIntegerForKey(SaveDataKey[n_DataKeyNum::eLossNum01].c_str());
			def->setIntegerForKey(SaveDataKey[n_DataKeyNum::eLossNum01].c_str(), lossNum + 1);

			auto markSprite = Sprite::create("img/UI/battle/deny.png");
			markSprite->setScale(0.3);
			markSprite->setPosition(m_playerMonsters[i]->getPosition());
			m_playerMonsters[i]->setColor(Color3B(150, 150, 150));
			m_marks->addChild(markSprite);
		}
		else if (winRes[i] == WIN)
		{
			int winNum = def->getIntegerForKey(SaveDataKey[n_DataKeyNum::eWinNum01].c_str());
			def->setIntegerForKey(SaveDataKey[n_DataKeyNum::eWinNum01].c_str(), winNum + 1);

			auto markSprite = Sprite::create("img/UI/battle/deny.png");
			markSprite->setScale(0.3);
			markSprite->setPosition(m_enemyMonsters[i]->getPosition());
			m_enemyMonsters[i]->setColor(Color3B(150, 150, 150));
			m_marks->addChild(markSprite);
		}
	}

	if (totalResult == WIN)
	{
		m_result = Sprite::create("img/UI/result/UI_B_22.png");
	}
	else if (totalResult == LOSE)
	{
		m_result = Sprite::create("img/UI/result/UI_B_23.png");
	}
	else
	{
		m_result = Sprite::create("img/UI/result/UI_B_014.png");
	}

	m_result->setPosition(visibleSize.width / 2, visibleSize.height / 1.5);
	m_result->setScale(m_Mag * 0.7);
	this->addChild(m_result);

	auto enlargeRes = ScaleBy::create(0.5, 1.3);
	auto smallenRes = ScaleTo::create(0.5, m_Mag * 0.7);
	auto growShrinkAnim = RepeatForever::create(Sequence::create(enlargeRes, smallenRes, NULL));

	m_result->runAction(growShrinkAnim);

	this->addChild(m_marks);

	m_resultFlag = totalResult;
	m_overviewMode = true;
	m_evolvingMode = false;
	m_standBy = false;
}

void ResultScene::expShare()
{
	m_expText = Node::create();

	auto fileU = FileUtils::getInstance();
	auto fileContent = fileU->getStringFromFile("data/monsterData.xml");

	mData.Parse(fileContent.c_str());
	UserDefault* def = UserDefault::getInstance();

	wipeResult();

	int totalXP[3];

	for (int i = 0; i < 3; i++)
	{
		m_playerMonsters[i]->setPositionX(visibleSize.width / 2.4);
		m_playerMonsters[i]->setScale(0.5);
		m_playerMonsters[i]->setColor(Color3B(255, 255, 255));

		int key = def->getIntegerForKey(SaveDataKey[n_DataKeyNum::eMonsterData01 + i].c_str());
		int playerLvl = atoi(mData.FirstChildElement()->FirstChildElement(MonsterNameData[key].c_str())->FirstChildElement("special")->FirstChildElement("level")->GetText());
		int playerRar = atoi(mData.FirstChildElement()->FirstChildElement(MonsterNameData[key].c_str())->FirstChildElement("rarity")->GetText());

		key = def->getIntegerForKey(SaveDataKey[n_DataKeyNum::eEnemyMonster01 + i].c_str());
		int enemyLvl = atoi(mData.FirstChildElement()->FirstChildElement(MonsterNameData[key].c_str())->FirstChildElement("special")->FirstChildElement("level")->GetText());
		int enemyRar = atoi(mData.FirstChildElement()->FirstChildElement(MonsterNameData[key].c_str())->FirstChildElement("rarity")->GetText());

		int difference = enemyLvl - playerLvl;
		int bonus = (enemyRar * 20) - (playerRar * 10);

		
		if (m_resultFlag == WIN)
		{
			totalXP[i] = BASEXP + (difference * 100) + bonus;
			if (winRes[i] == LOSE)
			{
				totalXP[i] = totalXP[i] / 2;
			}
		}
		else if (m_resultFlag == DRAW)
		{
			totalXP[i] = BASEXP + (difference * 100) + bonus;
			totalXP[i] = totalXP[i] / 2;

			if (winRes[i] == LOSE)
			{
				totalXP[i] = 0;
			}
		}
		else
		{
			totalXP[i] = 0;
		}
		
		int priorExperience = def->getIntegerForKey(SaveDataKey[n_DataKeyNum::eMonster1Exp + i].c_str());
		string XPText = "XP:" + Generic::intToStrnig(priorExperience);
		auto priorXP = Label::createWithTTF(XPText, "fonts/arial.ttf", 50);
		priorXP->setColor(Color3B::YELLOW);
		priorXP->enableOutline(Color4B::BLACK, 2);
		priorXP->setPosition(m_playerMonsters[i]->getPositionX() + 200, m_playerMonsters[i]->getPositionY());
		m_expText->addChild(priorXP);

		string newExperience = "+" + Generic::intToStrnig(totalXP[i]);

		auto newXP = Label::createWithTTF(newExperience, "fonts/arial.ttf", 40);
		newXP->setPosition(priorXP->getPositionX() + 170, m_playerMonsters[i]->getPositionY());
		newXP->setColor(Color3B::GREEN);
		newXP->enableOutline(Color4B::BLACK, 2);
		m_expText->addChild(newXP);

		int bothXP = priorExperience + totalXP[i];
		def->setIntegerForKey(SaveDataKey[n_DataKeyNum::eMonster1Exp + i].c_str(), bothXP);

		auto moveUp = MoveBy::create(0.3, Vec2(0, 20));
		auto moveDown = MoveBy::create(0.3, Vec2(0, -20));
		auto loop = RepeatForever::create(Sequence::create(moveUp, moveDown, NULL));
		newXP->runAction(loop);

		key = def->getIntegerForKey(SaveDataKey[n_DataKeyNum::eMonsterData01 + i].c_str());

		//check if evolve is available;
		if (m_resultFlag == WIN)
		{
			if (playerLvl < 2)
			{
				if (bothXP >= EVOLVE_COND)
				{
					if(key != 0)
					{
						m_evolvingMode = true;
						m_evolveState[i] = true;
					}
				}
				else
					m_evolveState[i] = false;
			}
		}
		
	}

	this->addChild(m_expText);

	m_overviewMode = false;
}

void ResultScene::wipeResult()
{
	this->removeChild(m_marks);
	this->removeChild(m_result);
	for (int i = 0; i < 3; i++)
	{
		//this->removeChild(m_playerMonsters[i]);
		this->removeChild(m_enemyMonsters[i]);
	}
}

bool ResultScene::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
    return true;
}

void ResultScene::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
    rtnHome();
}

void ResultScene::rtnHome()
{
	if (!m_overviewMode && !m_evolvingMode && !m_standBy)
	{
		auto nextScene = MenuScene::createScene();
		auto pScene = TransitionFade::create(0.5f, nextScene);
		Director::getInstance()->replaceScene(pScene);
	}
	
	if (m_overviewMode && !m_evolvingMode)
	{
		expShare();
	}
	else if (m_evolvingMode && !m_overviewMode)
	{
		evolve();
	}
}

void ResultScene::evolve()
{
	m_evolvingMode = false;
	m_standBy = true;
	this->removeChild(m_expText);

	for (int i = 0; i < 3; i++)
	{
		m_playerMonsters[i]->setPosition((visibleSize.width / 6) * ((i * 2) + 1), visibleSize.height / 2);
		m_playerMonsters[i]->setScale(0.8);
		m_playerMonsters[i]->setVisible(false);
	}

	
	m_descBG = Sprite::create("img/effect/effects/green/background_green_00014.png");
	Animation* anim = Animation::create();

	anim->addSpriteFrameWithFileName("img/effect/effects/green/background_green_00013.png");
	anim->addSpriteFrameWithFileName("img/effect/effects/green/background_green_00012.png");
	anim->addSpriteFrameWithFileName("img/effect/effects/green/background_green_00011.png");
	anim->addSpriteFrameWithFileName("img/effect/effects/green/background_green_00010.png");
	anim->addSpriteFrameWithFileName("img/effect/effects/green/background_green_00009.png");
	anim->addSpriteFrameWithFileName("img/effect/effects/green/background_green_00008.png");
	anim->addSpriteFrameWithFileName("img/effect/effects/green/background_green_00007.png");
	anim->addSpriteFrameWithFileName("img/effect/effects/green/background_green_00006.png");
	anim->addSpriteFrameWithFileName("img/effect/effects/green/background_green_00005.png");
	anim->addSpriteFrameWithFileName("img/effect/effects/green/background_green_00004.png");
	anim->addSpriteFrameWithFileName("img/effect/effects/green/background_green_00003.png");
	anim->addSpriteFrameWithFileName("img/effect/effects/green/background_green_00002.png");
	anim->addSpriteFrameWithFileName("img/effect/effects/green/background_green_00001.png");
	anim->addSpriteFrameWithFileName("img/effect/effects/green/background_green_00000.png");

	anim->setLoops(-1);
	anim->setDelayPerUnit(0.1f);
	//sprite->setColor(Color3B(100,100,100));
	m_descBG->runAction(Animate::create(anim));
	m_descBG->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	m_descBG->setScale(m_Mag * 1.5);

	this->addChild(m_descBG);
	

	checkEvolution(0);
}

void ResultScene::checkEvolution(int i)
{
	auto fileU = FileUtils::getInstance();

	auto fileContent = fileU->getStringFromFile("data/monsterData.xml");
	mData.Parse(fileContent.c_str());

	fileContent = fileU->getStringFromFile("data/animData.xml");
	doc.Parse(fileContent.c_str());

	UserDefault* def = UserDefault::getInstance();
	
	int j = i+1;
	CallFunc* nextCheck;
	if (j < 3)
	{
		nextCheck = CallFunc::create([this, j](){this->checkEvolution(j); });
	}
	if (m_evolveState[i])
	{
		int key = def->getIntegerForKey(SaveDataKey[n_DataKeyNum::eMonsterData01 + i].c_str());
		int level = atoi(mData.FirstChildElement()->FirstChildElement(MonsterNameData[key].c_str())->FirstChildElement("special")->FirstChildElement("level")->GetText());

		int change = 0;

		if (level == 0)
		{
			int winNum = def->getIntegerForKey(SaveDataKey[n_DataKeyNum::eWinNum01 + i].c_str());
			int lossNum = def->getIntegerForKey(SaveDataKey[n_DataKeyNum::eLossNum01 + i].c_str());
			if (winNum >= lossNum)
			{
				change = 1;
			}
			else if (lossNum > winNum)
			{
				change = 2;
			}
		}
		else
		{
			change = 2;
		}
		
		m_playerMonsters[i]->setVisible(true);
		m_playerMonsters[i]->setPosition(visibleSize.width / 2, visibleSize.height / 2);
		string spritePath = doc.FirstChildElement()->FirstChildElement(MonsterNameData[key + change].c_str())->FirstChildElement("spriteList")->FirstChildElement("animation")->FirstChildElement("stand")->GetText();
		auto evolution = Sprite::create(spritePath);
		evolution->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		evolution->setScale(m_playerMonsters[i]->getScale());
		evolution->setVisible(false);
		this->addChild(evolution);

		auto wait1 = DelayTime::create(0.4);
		auto longWait1 = DelayTime::create(0.8);
		auto darken1 = TintTo::create(0.1, Color3B::BLACK);
		auto lighten1 = TintTo::create(0.1, Color3B::WHITE);
		auto hide1 = Hide::create();
		auto show1 = Show::create();
		auto repeat = Repeat::create(Sequence::create(darken1, wait1, hide1, wait1, show1, lighten1, wait1, NULL), 4);
		
		Sequence* evoSequence;
		if (j == 3)
		{
			evoSequence = Sequence::create(longWait1, darken1, wait1, lighten1, repeat, longWait1, darken1, hide1, longWait1, longWait1, longWait1, hide1, NULL);
		}
		else
		{
			evoSequence = Sequence::create(longWait1, darken1, wait1, lighten1, repeat, longWait1, darken1, hide1, longWait1, longWait1, longWait1, hide1, nextCheck, NULL);
		}
		m_playerMonsters[i]->runAction(evoSequence);

		auto wait2 = DelayTime::create(0.4);
		auto longWait2 = DelayTime::create(0.8);
		auto show2 = Show::create();
		auto darken2 = TintTo::create(0.1, Color3B::BLACK);
		auto lighten2 = TintTo::create(0.1, Color3B::WHITE);
		auto hide2 = Hide::create();
		auto repeat2 = Repeat::create(Sequence::create(darken2, wait2, show2, wait2, hide2, darken2, wait2, NULL), 4);
		auto evoSequence2 = Sequence::create(longWait2, darken2, wait2, darken2, repeat2, longWait2, lighten2, show2, longWait2, longWait2, longWait2, hide2, NULL);
		evolution->runAction(evoSequence2);

		def->setIntegerForKey(SaveDataKey[n_DataKeyNum::eMonsterData01 + i].c_str(), (key + change));
		def->setIntegerForKey(SaveDataKey[n_DataKeyNum::eMonster1Exp + i].c_str(), 0);
		def->setBoolForKey(SaveDataKey[n_DataKeyNum::eKnownData01 + key + change].c_str(), true);
	}
	else
	{
		if (j < 3)
		this->runAction(nextCheck);
	}

	if (j == 3)
	{
		m_standBy = false;
	}
}

void ResultScene::eventHandler()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(ResultScene::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(ResultScene::onTouchEnded, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void ResultScene::backButton()
{
	string btn = "img/UI/menu/UI_M_009.png";
	string pushBtn = "img/UI/menu/UI_M_010.png";

	auto callBackItem = [](Ref *obj){
		auto nextScene = MenuScene::createScene();
		auto pScene = TransitionFade::create(0.5f, nextScene);
		Director::getInstance()->replaceScene(pScene);
	};

	auto btnItem = MenuItemImage::create(btn.c_str(),
		pushBtn.c_str(),
		callBackItem);
	btnItem->setScale(m_Mag);
	btnItem->setTag(SpriteTags::ReturnBtn);
	Menu* rtnBtn = Menu::create(btnItem, NULL);
	rtnBtn->setPosition(Vec2(visibleSize.width / 2,
		origin.y + btnItem->getContentSize().height));
	this->addChild(rtnBtn);
}

void ResultScene::displayBG()
{
	auto bg = Sprite::create("img/BG/menu.png");

	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	bg->setScale(m_Mag);
	this->addChild(bg);
}
