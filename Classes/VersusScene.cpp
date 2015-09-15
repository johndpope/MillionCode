#include "VersusScene.h"
#include "BattleScene.h"

using namespace cocos2d;
using namespace std;

enum SpriteTags
{
	ReturnBtn,
};

Scene* VersusScene::createScene() {
	auto scene = Scene::create();
	auto layer = VersusScene::create();
	scene->addChild(layer);
	return scene;
}

bool VersusScene::init() {
	if (!Layer::init()) { return false; }

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	m_Mag = Generic::getScreenMagnification(visibleSize);

	srand(time(NULL));

	difficultySelect();

	return true;
}

void VersusScene::difficultySelect()
{
	MenuItemFont::setFontSize(60);
	auto easyItem = MenuItemFont::create("EASY", CC_CALLBACK_1(VersusScene::runVersus, this, 0));
	easyItem->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height /6) * 4));
	auto mediumItem = MenuItemFont::create("MEDIUM", CC_CALLBACK_1(VersusScene::runVersus, this, 1));
	mediumItem->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height / 6) * 3));
	auto hardItem = MenuItemFont::create("HARD", CC_CALLBACK_1(VersusScene::runVersus, this, 2));
	hardItem->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height / 6) * 2));
	m_difficulty = Menu::create(easyItem, mediumItem, hardItem, NULL);
	m_difficulty->setPosition(Point::ZERO);
	this->addChild(m_difficulty);
}

bool VersusScene::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
	return true;
}

void VersusScene::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
	rtnHome();
}

void VersusScene::rtnHome()
{
	auto nextScene = BattleScene::createScene();
	auto pScene = TransitionSplitCols::create(0.8f, nextScene);
	Director::getInstance()->replaceScene(pScene);
}

void VersusScene::eventHandler()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(VersusScene::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(VersusScene::onTouchEnded, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void VersusScene::displayBG()
{
	auto particles = ParticleSystemQuad::create("img/BG/BattleBG/versus1.plist");
	particles->setPosition(visibleSize.width / 2, 0);
	
	this->addChild(particles);
}

void VersusScene::showVersus()
{
	//sprite init
	auto vsSprite = Sprite::create("img/UI/battle/vs.png");
	vsSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 1.3f));
	vsSprite->setScale(m_Mag*1.6f);
	vsSprite->setVisible(false);
	this->addChild(vsSprite);

	//shadow effect sprite init
	auto vsShadow = Sprite::create("img/UI/battle/vs.png");
	vsShadow->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 1.3f));
	vsShadow->setScale(m_Mag*1.6f);
	vsShadow->setVisible(false);
	vsShadow->setColor(Color3B::WHITE);
	vsShadow->setOpacity(128);
	this->addChild(vsShadow);

	//normal sprite animation
	auto show = Show::create();
	auto smallen = ScaleBy::create(0.3f, 0.7f);
	auto shake = CallFunc::create([this](){Generic::shake(this); });
	vsSprite->runAction(Sequence::create(show, smallen, shake, NULL));

	//shadow animation
	auto fadeOut = FadeIn::create(0.3f);
	auto fade = FadeOut::create(0.5f);
	auto showShadow = Show::create();
	auto enlarge = ScaleBy::create(0.5f, 2.0f);
	auto spawn = Spawn::create(fade, enlarge, NULL);
	vsShadow->runAction(Sequence::create(fadeOut, showShadow, spawn, NULL));
}

void VersusScene::showTeam()
{
	auto fileU = FileUtils::getInstance();
	auto fileContent = fileU->getStringFromFile("data/animData.xml");
	doc.Parse(fileContent.c_str());

	//-------------------------------------------------------------------------
	// Player Monsters
	//-------------------------------------------------------------------------

	UserDefault* def = UserDefault::getInstance();
	//Load paths for each monster in the party
	int key = def->getIntegerForKey(SaveDataKey[n_DataKeyNum::eMonsterData01].c_str()); //first monster
	auto m1SpritePath = doc.FirstChildElement()->FirstChildElement(MonsterNameData[key].c_str())->FirstChildElement("spriteList")->FirstChildElement("animation")->FirstChildElement("stand")->GetText();

	key = def->getIntegerForKey(SaveDataKey[n_DataKeyNum::eMonsterData02].c_str()); //second monster
	auto m2SpritePath = doc.FirstChildElement()->FirstChildElement(MonsterNameData[key].c_str())->FirstChildElement("spriteList")->FirstChildElement("animation")->FirstChildElement("stand")->GetText();

	key = def->getIntegerForKey(SaveDataKey[n_DataKeyNum::eMonsterData03].c_str()); //third monster
	auto m3SpritePath = doc.FirstChildElement()->FirstChildElement(MonsterNameData[key].c_str())->FirstChildElement("spriteList")->FirstChildElement("animation")->FirstChildElement("stand")->GetText();
	
	//create sprites
	auto monster1 = Sprite::create(m1SpritePath);
	auto monster2 = Sprite::create(m2SpritePath);
	auto monster3 = Sprite::create(m3SpritePath);

	//initialize sprites outside screen
	monster1->setPosition(Vec2(-300, visibleSize.height / 2));
	monster2->setPosition(Vec2(-400, visibleSize.height / 2));
	monster3->setPosition(Vec2(-500, visibleSize.height / 2));

	//adjust sprite direction and scaling
	monster1->setScale(m_Mag*0.9);
	monster1->setScaleX(-m_Mag*0.9);
	monster2->setScale(m_Mag*0.75);
	monster2->setScaleX(-m_Mag*0.75);
	monster3->setScale(m_Mag*0.65);
	monster3->setScaleX(-m_Mag*0.65);

	//add monsters
	this->addChild(monster3);
	this->addChild(monster2);
	this->addChild(monster1);

	//animate monsters
	auto monster1Move = MoveBy::create(1.0f, Vec2(750, -100));
	auto monster2Move = MoveBy::create(1.0f, Vec2(690, 50));
	auto monster3Move = MoveBy::create(1.0f, Vec2(610, 200));
	auto monster1StandMove = MoveTo::create(25.0f, Vec2(visibleSize.width / 2, visibleSize.height / 2));
	auto monster2StandMove = MoveTo::create(25.0f, Vec2(visibleSize.width / 2, visibleSize.height / 2));
	auto monster3StandMove = MoveTo::create(25.0f, Vec2(visibleSize.width / 2, visibleSize.height / 2));

	monster1->runAction(Sequence::create(monster1Move, monster1StandMove, NULL));
	monster2->runAction(Sequence::create(monster2Move, monster2StandMove, NULL));
	monster3->runAction(Sequence::create(monster3Move, monster3StandMove, NULL));


	//-------------------------------------------------------------------------
	// Enemy Monsters
	//-------------------------------------------------------------------------
	int starterArray[12];
	switch (m_diffLevel)
	{
		//Eazy mode monsters
	case 0:
		starterArray[0] = 0;
		starterArray[1] = 1;
		starterArray[2] = 6;
		starterArray[3] = 11;
		starterArray[4] = 16;
		starterArray[5] = 21;
		starterArray[6] = 26;
		starterArray[7] = 0;
		starterArray[8] = 11;
		starterArray[9] = 8;
		starterArray[10] = 1;
		starterArray[11] = 26;
		break;
		//Medium mode monsters
	case 1:
		starterArray[0] = 2;
		starterArray[1] = 3;
		starterArray[2] = 7;
		starterArray[3] = 8;
		starterArray[4] = 12;
		starterArray[5] = 13;
		starterArray[6] = 17;
		starterArray[7] = 18;
		starterArray[8] = 22;
		starterArray[9] = 23;
		starterArray[10] = 27;
		starterArray[11] = 28;
		break;
		//Hard mode monsters
	case 2:
		starterArray[0] = 4;
		starterArray[1] = 5;
		starterArray[2] = 9;
		starterArray[3] = 10;
		starterArray[4] = 14;
		starterArray[5] = 15;
		starterArray[6] = 19;
		starterArray[7] = 20;
		starterArray[8] = 24;
		starterArray[9] = 25;
		starterArray[10] = 29;
		starterArray[11] = 30;
		break;
	default:
		break;
	}

	//load paths and save the generated monsters
	
	
	int enemyMonster = starterArray[rand() % 12];
	def->setIntegerForKey(SaveDataKey[n_DataKeyNum::eEnemyMonster01].c_str(), enemyMonster);
	def->setBoolForKey(SaveDataKey[n_DataKeyNum::eKnownData01 + enemyMonster].c_str(), true);
	auto e1SpritePath = doc.FirstChildElement()->FirstChildElement(MonsterNameData[enemyMonster].c_str())->FirstChildElement("spriteList")->FirstChildElement("animation")->FirstChildElement("stand")->GetText();
	enemyMonster = starterArray[rand() % 10];
	def->setIntegerForKey(SaveDataKey[n_DataKeyNum::eEnemyMonster02].c_str(), enemyMonster);
	def->setBoolForKey(SaveDataKey[n_DataKeyNum::eKnownData01 + enemyMonster].c_str(), true);
	auto e2SpritePath = doc.FirstChildElement()->FirstChildElement(MonsterNameData[enemyMonster].c_str())->FirstChildElement("spriteList")->FirstChildElement("animation")->FirstChildElement("stand")->GetText();
	enemyMonster = starterArray[rand() % 10];
	def->setIntegerForKey(SaveDataKey[n_DataKeyNum::eEnemyMonster03].c_str(), enemyMonster);
	def->setBoolForKey(SaveDataKey[n_DataKeyNum::eKnownData01 + enemyMonster].c_str(), true);
	auto e3SpritePath = doc.FirstChildElement()->FirstChildElement(MonsterNameData[enemyMonster].c_str())->FirstChildElement("spriteList")->FirstChildElement("animation")->FirstChildElement("stand")->GetText();

	//create sprites
	auto enemy1 = Sprite::create(e1SpritePath);
	auto enemy2 = Sprite::create(e2SpritePath);
	auto enemy3 = Sprite::create(e3SpritePath);

	//initialize sprites outside screen
	enemy1->setPosition(Vec2(visibleSize.width + 300, visibleSize.height/2));
	enemy2->setPosition(Vec2(visibleSize.width + 400, visibleSize.height / 2));
	enemy3->setPosition(Vec2(visibleSize.width + 500, visibleSize.height / 2));

	//adjust sprite scaling
	enemy1->setScale(m_Mag*0.9);
	enemy2->setScale(m_Mag*0.75);
	enemy3->setScale(m_Mag*0.65);

	//add enemies
	this->addChild(enemy3);
	this->addChild(enemy2);
	this->addChild(enemy1);

	//animate enemies
	auto enemy1Move = MoveBy::create(1.0f, Vec2(-750, -100));
	auto enemy2Move = MoveBy::create(1.0f, Vec2(-690, 50));
	auto enemy3Move = MoveBy::create(1.0f, Vec2(-610, 200));
	auto enemy1StandMove = MoveTo::create(25.0f, Vec2(visibleSize.width / 2, visibleSize.height / 2));
	auto enemy2StandMove = MoveTo::create(25.0f, Vec2(visibleSize.width / 2, visibleSize.height / 2));
	auto enemy3StandMove = MoveTo::create(25.0f, Vec2(visibleSize.width / 2, visibleSize.height / 2));

	enemy1->runAction(Sequence::create(enemy1Move, enemy1StandMove, NULL));
	enemy2->runAction(Sequence::create(enemy2Move, enemy2StandMove, NULL));
	enemy3->runAction(Sequence::create(enemy3Move, enemy3StandMove, NULL));
	
}

void VersusScene::runVersus(cocos2d::Ref *pSender, int difficulty)
{
	UserDefault* def = UserDefault::getInstance();
	def->setIntegerForKey(SaveDataKey[n_DataKeyNum::eDiffLevel].c_str(), difficulty);

	m_difficulty->setVisible(false);
	m_difficulty->setEnabled(false);

	m_diffLevel = difficulty;


	auto tmp = Node::create();
	this->addChild(tmp);

	//Sequence of actions
	auto shortWait = FadeOut::create(0.5f);
	auto midWait = FadeOut::create(1.0f);
	auto longWait = FadeOut::create(3.0f);
	auto background = CallFunc::create([this](){this->displayBG(); });
	auto team = CallFunc::create([this](){this->showTeam(); });
	auto startBattle = CallFunc::create([this](){this->rtnHome(); });
	auto versus = CallFunc::create([this](){this->showVersus(); });

	tmp->runAction(Sequence::create(shortWait, background, team, midWait, versus, longWait, startBattle, NULL));
}